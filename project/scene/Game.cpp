#include<DxLib.h>
#include "Game.h"
#include "../input/InputID.h"
#include "Action/Action.h"
#include "Gun/Gun.h"
#include "Memory/Memory.h"
#include "Puzle/Puzle.h"
#include "Shooting/Shooting.h"
#include "Snake/Snake.h"

Game::Game()
{
    Init();
}
Game::~Game()
{
}

bool Game::Init(void)
{
    playCnt = 1;

    gameList[0].name = Glist::ACTION;
    gameList[1].name = Glist::SHOOTING;
    gameList[2].name = Glist::SNAKE;
    gameList[3].name = Glist::MEMORY;
    gameList[4].name = Glist::GUN;
    gameList[5].name = Glist::PUZLE;

    nowTime = std::chrono::system_clock::now();

    return true;
}

UniScene Game::UpDate(UniScene scene, KeyDate keyData)
{
    oldTime = nowTime;
    nowTime = std::chrono::system_clock::now();
    auto poorTime = std::chrono::duration_cast
        <std::chrono::microseconds>(nowTime - oldTime);
    double delta = poorTime.count() / 1000000.0;

    if (play)
    {
        if (readyTime <= 0.0)
        {
            if (finishTime <= 0.0)
            {
                int result = game->UpDate(keyData, delta);
                if (result != -1)
                {
                    finishTime = 2.0;
                    gameList[playCnt].point = result;
                }
            }
            else
            {
                finishTime -= delta;
                if (finishTime <= 0.0)
                {
                    play = false;
                    game.release();
                    ++playCnt;
                }
            }
        }
        else readyTime -= delta;
    }
    else
    {
        if (playCnt < 6)
        {
            TestUpDate(keyData);
        }
        else
        {
            resultTime += delta;
        }
        
    }
    return std::move(scene);
}

void Game::TestUpDate(KeyDate keyData)
{
    if (keyData[InputID::SPACE][Trg::Now] &&
        !keyData[InputID::SPACE][Trg::Old])
    {
        switch (gameList[playCnt].name)
        {
        case Glist::ACTION:
            game = std::make_unique<Action>();
            break;
        case Glist::SHOOTING:
            game = std::make_unique<Shooting>();
            break;
        case Glist::PUZLE:
            game = std::make_unique<Puzle>();
            break;
        case Glist::SNAKE:
            game = std::make_unique<Snake>();
            break;
        case Glist::GUN:
            game = std::make_unique<Gun>();
            break;
        case Glist::MEMORY:
            game = std::make_unique<Memory>();
            break;
        default:
            break;
        }
        
        readyTime = 2.0;
        play = true;
    }
}

void Game::Draw(void)
{
    if (play)
    {
        game->Draw();

        if (readyTime > 0.0)
        {
            DrawBox(200, 200, 500, 500, 0xff0000, true);
        }
        if (finishTime > 0.0)
        {
            DrawBox(200, 200, 500, 500, 0x0000ff, true);
        }
    }
    else
    {
        DrawString(0, 0, "GameScene", 0xffffff);
        GraphDraw();

        if (playCnt < 6)
        {
            // ŽŸ‚ÍOO‚Å‚·
        }
        else
        {
            resultDraw();
        }
    }
}

void Game::GraphDraw(void)
{
    int maxsize = 250;
    Vector2F oldDiff = { cosf(DX_PI_F / 3 * 5 - DX_PI_F / 2),sinf(DX_PI_F / 3 * 5 - DX_PI_F / 2) };
    for (int a = 0; a < 6; ++a)
    {
        float angle = DX_PI_F / 3 * a - DX_PI_F / 2;

        Vector2F diff = { cosf(angle),sinf(angle) };

        DrawLine(384, 384,
                384 + (diff.x_ * maxsize), 384 + (diff.y_ * maxsize),
                0xffffff);
        for (int b = 1; b <= 4; ++b)
        {
            DrawLine(384 + (oldDiff.x_ * maxsize / 4 * b), 384 + (oldDiff.y_ * maxsize / 4 * b),
                    384 + (diff.x_ * maxsize / 4 * b), 384 + (diff.y_ * maxsize / 4 * b),
                    0x999999);
        }

        if (a % 3 == 0)
        {
            DrawBox(384 + (diff.x_ * 300) - 64, 384 + (diff.y_ * 300) - 32,
                384 + (diff.x_ * 300) + 64, 384 + (diff.y_ * 300) + 32,
                0xff0000, true);
        }
        else if (a / 3 == 0)
        {
            DrawBox(384 + (diff.x_ * 300) - 32, 384 + (diff.y_ * 300) - 32,
                384 + (diff.x_ * 300) + 96, 384 + (diff.y_ * 300) + 32,
                0xff0000, true);
        }
        else
        {
            DrawBox(384 + (diff.x_ * 300) - 96, 384 + (diff.y_ * 300) - 32,
                384 + (diff.x_ * 300) + 32, 384 + (diff.y_ * 300) + 32,
                0xff0000, true);
        }

        oldDiff = diff;
    }

}

void Game::resultDraw(void)
{
    int maxsize = 200;

    double _time = resultTime < 1.0 ? resultTime : 1.0;

    int oldsize = maxsize / 100 * min(100, gameList[5].point);
    Vector2F oldDiff = { cosf(DX_PI_F / 3 * 5 - DX_PI_F / 2),sinf(DX_PI_F / 3 * 5 - DX_PI_F / 2) };

    SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 / 2);

    for (int a = 0; a < 6; ++a)
    {
        float angle = DX_PI_F / 3 * a - DX_PI_F / 2;

        Vector2F diff = { cosf(angle),sinf(angle) };
        int size = maxsize / 100 * min(100, gameList[a].point);

        DrawTriangle(384, 384,
                    384 + (diff.x_ * size * _time), 384 + (diff.y_ * size * _time),
                    384 + (oldDiff.x_ * oldsize * _time), 384 + (oldDiff.y_ * oldsize * _time),
                    0xff0000, true);
 
        oldDiff = diff;
        oldsize = size;
    }

    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}
