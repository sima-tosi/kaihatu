#include "Snake.h"
#include "../../input/InputID.h"
#include <DxLib.h>

Snake::Snake()
{
    Init();
}
Snake::~Snake()
{
}

void Snake::Init(void)
{
    Player a;
    a.pos = {1,1};
    a.ent = DIR::LEFT;
    a.exit = DIR::RIGHT;

    for (int b = 0; b < 3; b++)
    {
        body.push_back(a);
    }

    obs.resize(10 * 10);
    count = 0;
    moveDir = { DIR::RIGHT,DIR::RIGHT };
    turn = false;

    timeLimit = 30.0;
    point = 0;

    SetItem();
    breakTime = 0.0;
}

void Snake::GetItem(void)
{
    body.push_back(body[body.size() - 1]);
    point += 5;

    timeLimit += 5.0;
    if (item.destor) breakTime = 3.0;

    SetItem();

    SetObs();
}
void Snake::SetItem(void)
{
    ++itemCnt;
    if (itemCnt % 5 == 0) item.destor = true;
    else item.destor = false;

    item.pos = { rand() % 10,rand() % 10 };
    item.limit = MAX_TIME;
}

void Snake::SetObs(void)
{
    bool Hit = false;
    int obsPos;
    do
    {
        Hit = false;
        obsPos = rand() % 100;
        for (auto a : body)
        {
            if (a.pos.y_ * 10 + a.pos.x_ == obsPos)
            {
                Hit = true;
                break;
            }
        }
        if (body[0].pos.x_ + 1 == obsPos || body[0].pos.x_ - 1 == obsPos ||
            body[0].pos.y_ + 1 == obsPos || body[0].pos.y_ - 1 == obsPos)
        {
            Hit = true;
            break;
        }

    } while (Hit);
    obs[obsPos] = true;
}
void Snake::HitObs(int pos)
{
    if(obs[pos])
    {
        if (breakTime <= 0.0)
        {
            miss = true;
        }
        else
        {
            obs[pos] = false;
            ++point;
        }
    }
}

int Snake::UpDate(KeyDate keyData,double delta)
{
    if (keyData[InputID::UP][Trg::Now] &&
        !keyData[InputID::UP][Trg::Old])
    {
        if (moveDir.first != DIR::DOWN)
        {
            moveDir.second = DIR::UP;
        }
    }
    else if (keyData[InputID::DOWN][Trg::Now] &&
        !keyData[InputID::DOWN][Trg::Old])
    {
        if (moveDir.first != DIR::UP)
        {
            moveDir.second = DIR::DOWN;
        }
    }
    else if (keyData[InputID::LEFT][Trg::Now] &&
        !keyData[InputID::LEFT][Trg::Old])
    {
        if (moveDir.first != DIR::RIGHT)
        {
            moveDir.second = DIR::LEFT;
        }
    }
    else if (keyData[InputID::RIGHT][Trg::Now] &&
        !keyData[InputID::RIGHT][Trg::Old])
    {
        if (moveDir.first != DIR::LEFT)
        {
            moveDir.second = DIR::RIGHT;
        }
    }

    if (count >= 0.25)
    {
        count -= 0.25;

        if (turn)
        {
            body[0].ent = static_cast<DIR>((moveDir.first + 2) % 4);
            body[0].exit = moveDir.second;
            moveDir.first = moveDir.second;

            for (int a = 1; a < body.size(); ++a)
            {
                if (body[a].pos == body[0].pos)
                {
                    miss = true;
                }
            }

            if (body[0].pos == item.pos)
            {
                GetItem();
            }
        }
        else
        {
            for (int b = body.size() - 1; b > 0; --b)
            {
                body[b] = body[b - 1];

            }

            switch (body[0].exit)
            {
            case UP:
                --body[0].pos.y_;
                break;
            case DOWN:
                ++body[0].pos.y_;
                break;
            case LEFT:
                --body[0].pos.x_;
                break;
            case RIGHT:
                ++body[0].pos.x_;
                break;
            default:
                break;
            }

            if (body[0].pos.x_ >= 10 || body[0].pos.x_ < 0 ||
                body[0].pos.y_ >= 10 || body[0].pos.y_ < 0)
            {
                miss = true;
            }
            else HitObs(body[0].pos.y_ * 10 + body[0].pos.x_);
        }

        turn = !turn;
    }

    if (item.limit <= 0.0)  SetItem();
    if (timeLimit <= 0.0)miss = true;

    if (keyData[InputID::SPACE][Trg::Now] &&
        !keyData[InputID::SPACE][Trg::Old])
    {
        return 0;
    }

    item.limit -= delta;
    count += delta;
    timeLimit -=delta;
    breakTime -= delta;

    if (miss) return point;

    return -1;
}

void Snake::Draw(void)
{
    for (auto b : body)
    {
        DrawCircle(b.pos.x_ * 50 + 25,
            b.pos.y_ * 50 + 55, 10, 0xffff00);
    }
    for (int x = 0; x < 10; ++x)
    {
        for (int y = 0; y < 10; ++y)
        {
            DrawBox(x * 50, y * 50 + 30,
                (x + 1) * 50, (y + 1) * 50 + 30,
                0x00ffff, obs[y * 10 + x]);
            if (item.pos.x_ == x && item.pos.y_ == y)
            {
                DrawCircle(x * 50 + 25, y * 50 + 55,
                    8, 0xff0000,item.destor);
                DrawLine(x * 50, y * 50 + 70,
                    x * 50 + 50 * (item.limit / MAX_TIME), y * 50 + 70, 0xff0000,5);
            }
        }
    }
    DrawLine(0, 10,
        700 * (timeLimit / 100), 10, 0xff0000, 5);
    DrawLine(0, 15,
        700 * (breakTime / 3), 15, 0xff0000, 5);
    //DrawString(0, 0, "SnakeScene", 0xffffff);
    if(miss) DrawString(50, 0, "miss", 0xffffff);
}


