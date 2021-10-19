#include "Gun.h"
#include <DxLib.h>

Gun::Gun()
{
    Init();
}
Gun::~Gun()
{
}

void Gun::Init(void)
{
    shotPos = { 640,360 };

    targetCnt = shotCnt = 30;

    SetTarget();

    point = 0;
}

void Gun::SetTarget(void)
{
    int start = rand() % 5 + 1;
    int goal = rand() % 5 + 1;

    Target target;

    target.pos = { (float)((224 * start) - 32) ,626.0f };
    target.size = 32;
    target.vec = { 2.3f * (goal - start),-25 };
    target.life = true;

    targets.push_back(target);

    --targetCnt;
}

int Gun::UpDate(KeyDate keyData,double delta)
{
    if (keyData[InputID::UP][Trg::Now])
    {
        shotPos.y_ -= 10;
    }
    if (keyData[InputID::DOWN][Trg::Now])
    {
        shotPos.y_ += 10;
    }
    if (keyData[InputID::LEFT][Trg::Now])
    {
        shotPos.x_ -= 10;
    }
    if (keyData[InputID::RIGHT][Trg::Now])
    {
        shotPos.x_ += 10;
    }

    for (auto& target : targets)
    {
        target.vec.y_ += 0.5;
        target.pos += target.vec;

        if (target.pos.y_ > 720 + target.size)
        {
            target.life = false;
        }
    }

    if (keyData[InputID::SPACE][Trg::Now] &&
        !keyData[InputID::SPACE][Trg::Old])
    {
        if (shotCnt > 0)
        {
            for (auto& target : targets)
            {
                Vector2F kyori = shotPos - target.pos;
                if (pow(kyori.x_, 2) + pow(kyori.y_, 2)
                    < pow(target.size, 2))
                {
                    target.life = false;
                    ++point;
                }
            }
            --shotCnt;
        }
    }

    auto o = std::remove_if(targets.begin(), targets.end(),
        [](auto&& target) {return !(target.life); });
    targets.erase(o, targets.end());

    if (targets.size() == 0)
    {
        if (targetCnt > 0)
        {
            SetTarget();
        }
        else return point;
    }

    return -1;
}

void Gun::Draw(void)
{
    DrawString(0, 0, "GunScene", 0xffffff);

    for (int b = 0; b < shotCnt; ++b)
    {
        DrawLine(10 * b + 10, 10, 10 * b + 10, 20, 0xffff00, 5);
    }

    for (auto target : targets)
    {
        DrawCircle(target.pos.x_, target.pos.y_,
            target.size, 0xffffff, true);
    }

    for (int b = 1; b <= 5; ++b)
    {
        DrawBox((224 * b) - 64, 594, (224 * b), 720, 0xffffff, true);
    }

    DrawCircle(shotPos.x_, shotPos.y_, 20, 0xff0000,false);
    DrawLine(shotPos.x_ + 20, shotPos.y_,
            shotPos.x_ - 20, shotPos.y_,
            0xff0000);
    DrawLine(shotPos.x_, shotPos.y_ + 20,
        shotPos.x_, shotPos.y_ - 20,
        0xff0000);
}