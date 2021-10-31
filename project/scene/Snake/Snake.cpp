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

    timeLimit = MAX_TIME;
    point = 0;

    SetItem();
    breakTime = 0.0;

    screen = MakeScreen(64 * 10, 64 * 10);
}

void Snake::GetItem(void)
{
    body.push_back(body[body.size() - 1]);
    point += 5;

    timeLimit += 3.5;
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

            body[0].ent = static_cast<DIR>((moveDir.first + 2) % 4);

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

    item.limit -= delta;
    count += delta;
    timeLimit -=delta;
    breakTime -= delta;

    if (miss) return point;

    return -1;
}

void Snake::Draw(void)
{
    int size = 64;

    DrawBox(0, 0, size * 12, size * 12, 0x0000ff, true);

    SetDrawScreen(screen);
    ClsDrawScreen();

    for (int x = 0; x < 10; ++x)
    {
        for (int y = 0; y < 10; ++y)
        {
            if (obs[y * 10 + x])
            {
                DrawBox(x * size, y * size,
                    (x + 1) * size, (y + 1) * size,
                    0x999999, true);
            }
            else
            {
                DrawBox(x * size, y * size,
                    (x + 1) * size, (y + 1) * size,
                    0x00ff00, true);
            }

            DrawBox(x * size, y * size,
                (x + 1) * size, (y + 1) * size,
                0xffffff, false);

            if (item.pos.x_ == x && item.pos.y_ == y)
            {
                if (item.destor)
                    DrawCircle(x * size + size / 2, y * size + size / 2,
                        8, 0xffff00, true);
                else
                    DrawCircle(x * size + size / 2, y * size + size / 2,
                        8, 0xff0000,true);

                DrawLine(x * size, y * size + (size / 4 * 3),
                        x * size + size * (item.limit / MAX_TIME),
                        y * size+ (size / 4 * 3), 0xff0000,5);
            }
        }
    }

    int sColor = 0x000000;
    if (breakTime > 0.0) sColor = 0xffff00;

    // ‚ ‚½‚Ü
    Vector2 ePos = body[0].pos * Vector2{ size,size } + Vector2{ size / 2,size / 2 };
    Vector2 sPos = ePos;
    switch (body[0].ent)
    {
    case DIR::DOWN:
        sPos.y_ += size / 2;
        break;
    case DIR::LEFT:
        sPos.x_ -= size / 2;
        break;
    case DIR::RIGHT:
        sPos.x_ += size / 2;
        break;
    case DIR::UP:
        sPos.y_ -= size / 2;
        break;
    }
    if (!turn)
    {
        DrawLine(sPos.x_, sPos.y_, ePos.x_, ePos.y_, sColor, 3);
        sPos = ePos;
        switch (body[0].exit)
        {
        case DIR::DOWN:
            ePos.y_ += size / 2;
            break;
        case DIR::LEFT:
            ePos.x_ -= size / 2;
            break;
        case DIR::RIGHT:
            ePos.x_ += size / 2;
            break;
        case DIR::UP:
            ePos.y_ -= size / 2;
            break;
        }
    }
    Vector2 diff = ePos - sPos;
    DrawLine(sPos.x_, sPos.y_,
        sPos.x_ + diff.x_ * (count/ 0.25), sPos.y_ + diff.y_ * (count / 0.25),
        sColor, 3);

    // ‚©‚ç‚¾
    for (int no =1;no < body.size() - 1;++no)
    {
        Vector2 ePos = body[no].pos * Vector2{ size,size } + Vector2{ size / 2,size / 2 };
        Vector2 sPos = ePos;
        switch (body[no].ent)
        {
        case DIR::DOWN:
            sPos.y_ += size / 2;
            break;
        case DIR::LEFT:
            sPos.x_ -= size / 2;
            break;
        case DIR::RIGHT:
            sPos.x_ += size / 2;
            break;
        case DIR::UP:
            sPos.y_ -= size / 2;
            break;
        }
        DrawLine(sPos.x_, sPos.y_, ePos.x_, ePos.y_, sColor, 3);
        sPos = ePos;
        switch (body[no].exit)
        {
        case DIR::DOWN:
            ePos.y_ += size / 2;
            break;
        case DIR::LEFT:
            ePos.x_ -= size / 2;
            break;
        case DIR::RIGHT:
            ePos.x_ += size / 2;
            break;
        case DIR::UP:
            ePos.y_ -= size / 2;
            break;
        }
        DrawLine(sPos.x_, sPos.y_, ePos.x_, ePos.y_, sColor, 3);
    }

    // ‚µ‚Á‚Û
    int no = body.size() - 1;
    ePos = body[no].pos * Vector2{ size,size } + Vector2{ size / 2,size / 2 };
    sPos = ePos;
    switch (body[no].exit)
    {
    case DIR::DOWN:
        sPos.y_ += size / 2;
        break;
    case DIR::LEFT:
        sPos.x_ -= size / 2;
        break;
    case DIR::RIGHT:
        sPos.x_ += size / 2;
        break;
    case DIR::UP:
        sPos.y_ -= size / 2;
        break;
    }
    if (turn)
    {
        DrawLine(sPos.x_, sPos.y_, ePos.x_, ePos.y_, sColor, 3);
        sPos = ePos;
        switch (body[no].ent)
        {
        case DIR::DOWN:
            ePos.y_ += size / 2;
            break;
        case DIR::LEFT:
            ePos.x_ -= size / 2;
            break;
        case DIR::RIGHT:
            ePos.x_ += size / 2;
            break;
        case DIR::UP:
            ePos.y_ -= size / 2;
            break;
        }
    }
    diff = ePos - sPos;
    DrawLine(sPos.x_, sPos.y_,
        sPos.x_ + diff.x_ *  (1 - (count / 0.25)), sPos.y_ + diff.y_ * (1 - (count / 0.25)),
        sColor, 3);

    SetDrawScreen(DX_SCREEN_BACK);

    DrawGraph(size, size, screen, true);

    DrawLine(780, 768,
        780, 768 - (768 * (timeLimit / MAX_TIME)), 0xff0000, 10);
    DrawLine(800, 768,
        800, 768 - (768 * (breakTime / 3.0)), 0x00ff00, 10);

    //DrawString(0, 0, "SnakeScene", 0xffffff);
    if(miss) DrawString(50, 0, "miss", 0xffffff);
}


