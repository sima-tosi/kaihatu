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
    shotPos = { 512,360 };

    targetCnt = shotCnt = 30;

    SetTarget();

    targetImage = LoadGraph("image/Gun/target.png");
    bangImage = LoadGraph("image/Gun/bang.png");
    gunImage = LoadGraph("image/Gun/gun.png");

    point = 0;
}

void Gun::SetTarget(void)
{
    int start = rand() % 5 + 1;
    int goal = rand() % 5 + 1;

    Target target;

    target.pos = { (float)((1024 / 6 * start)) ,626.0f };
    target.size = 30;
    target.vec = { 1.0f * (goal - start),-25.0f };
    target.life = true;

    targets.push_back(target);

    --targetCnt;
}

int Gun::UpDate(KeyDate keyData,double delta)
{
    downTime += delta;

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
                    HitTarget ht;
                    ht.pos = target.pos;
                    ht.size = target.size;
                    ht.time = 0.5;
                    hTargets.emplace_back(ht);
                }
            }
            --shotCnt;
        }
    }

    for (auto& ht : hTargets)
    {
        ht.time -= delta;
    }

    auto o = std::remove_if(targets.begin(), targets.end(),
        [](auto&& target) {return !(target.life); });
    targets.erase(o, targets.end());
    auto ho = std::remove_if(hTargets.begin(), hTargets.end(),
        [](auto&& target) {return target.time <= 0.0; });
    hTargets.erase(ho, hTargets.end());

    if (downTime >= 2.0)
    {
        downTime = 0.0;
        if (targetCnt > 0)
        {
            SetTarget();
        }
        else
        {
            if(targets.size() == 0)
            return point * 4;
        }
    }

    return -1;
}

void Gun::Draw(void)
{
    DrawString(0, 0, "GunScene", 0xffffff);

    for (int b = 0; b < shotCnt; ++b)
    {
        DrawGraph(10 * b + 10, 10,
            gunImage, true);
    }

    for (auto ht : hTargets)
    {
        DrawGraph(ht.pos.x_ - ht.size,
            ht.pos.y_ - ht.size,
            bangImage, true);
    }
    for (auto target : targets)
    {
        DrawGraph(target.pos.x_ - target.size,
            target.pos.y_ - target.size,
            targetImage, true);
    }

    for (int b = 1; b <= 5; ++b)
    {
        DrawBox ((1024 / 6 * b) - 32, 594, (1024 / 6 * b) + 32, 768, 0xffffff, true);
    }

    DrawCircle(shotPos.x_, shotPos.y_, 20, 0xff0000,false);
    DrawLine(shotPos.x_ + 20, shotPos.y_,
            shotPos.x_ - 20, shotPos.y_,
            0xff0000);
    DrawLine(shotPos.x_, shotPos.y_ + 20,
        shotPos.x_, shotPos.y_ - 20,
        0xff0000);
}