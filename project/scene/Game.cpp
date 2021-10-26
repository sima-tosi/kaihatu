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
    gameList[2].name = Glist::PUZLE;
    gameList[3].name = Glist::SNAKE;
    gameList[4].name = Glist::GUN;
    gameList[5].name = Glist::MEMORY;

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
        int result = game->UpDate(keyData,delta);
        if (result != -1)
        {
            gameList[playCnt].point = result;
            play = false;
            game.release();
            ++playCnt;
        }
    }
    else
    {
        if (playCnt < 6)
        {
            TestUpDate(keyData);
        }
        else
        {

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
        
        play = true;
    }
}

void Game::Draw(void)
{
    if (play)
    {
        game->Draw();
    }
    else
    {
        DrawString(0, 0, "GameScene", 0xffffff);
    }
}
