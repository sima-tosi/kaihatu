#include "ShBoss.h"
#include "ShPlayer.h"
#include "Shooting.h"
#include <DxLib.h>

ShBoss::ShBoss(Shooting* _shooting,ShPlayer* _player)
{
    player = _player;
    shooting = _shooting;
    size = { 128,256};
    hitSize = { 32,32 };
    pos = { 1024 + 64,384 };

    shotPos.emplace_back(0, -64);
    shotPos.emplace_back(0, -128);
    shotPos.emplace_back(0, 64);
    shotPos.emplace_back(0, 128);
    escapeTime = 120.0;

    life = MAX_LIFE;
    vecY = 1;
    bossMove = BossMove::Entry;
}

ShBoss::~ShBoss()
{
}

void ShBoss::Init(void)
{
}

void ShBoss::UpDate(double delta)
{
    switch (bossMove)
    {
    case BossMove::Entry:
        pos.x_ -= 3;
        if (pos.x_ <= 1024 - size.x_ - 64)
            bossMove = BossMove::Stay;
        break;
    case BossMove::Stay:
        pos.y_ += 3 * vecY;
        if (pos.y_ + size.y_ >= 768) vecY = -1;
        if (pos.y_ - size.y_ <= 0) vecY = 1;
        escapeTime -= delta;
        if(escapeTime <= 0.0)
            bossMove = BossMove::EsCape;
        break;
    case BossMove::EsCape:
        pos.x_ += 3;
        if (pos.x_ >= 1024 + size.x_)
            escape = true;
        break;
    default:
        break;
    }

    shot1Time += delta;
    if (shot1Time > 0.25)
    {
        shot1Time = 0.0;
        for (auto shotpos : shotPos)
        {
            Shot2(pos - shotpos);
        }
    }
    if (life <= MAX_LIFE / 2)
    {
        shot2Time += delta;
        if (shot2Time > 0.5)
        {
            shot2Time = 0.0;
            for (auto shotpos : shotPos)
            {
                Shot1(pos - shotpos);
            }
        }
        if (life <= MAX_LIFE / 4)
        {
            shot3Time += delta;
            if (shot3Time < 1.0)
            {
                Shot3({ pos.x_ - size.x_,pos.y_ });
            }
            else if (shot3Time > 3.0)
            {
                shot3Time = 0.0;
            }
           
        }
    }
}

void ShBoss::Draw(void)
{
    DrawBox(pos.x_ - size.x_, pos.y_ - size.y_,
        pos.x_ + size.x_, pos.y_ + size.y_,
        0x00ffff, true);
    DrawBox(pos.x_ - hitSize.x_, pos.y_ - hitSize.y_,
        pos.x_ + hitSize.x_, pos.y_ + hitSize.y_,
        0xff0000, true);
    DrawCircle(pos.x_ + shotPos1.x_, pos.y_ + shotPos1.y_,
        5, 0xffff00);
    DrawCircle(pos.x_ + shotPos2.x_, pos.y_ + shotPos2.y_,
        5, 0xffff00);

    DrawLine(0, 10, 1028 / 100 * life, 10, 0xffffff, 10);
    DrawLine(0, 20, 1028 * (escapeTime / 120.0), 20, 0x00ffff, 10);
}

bool ShBoss::PlayerHit(Vector2F pPos, Vector2F pSize)
{
    return (pPos.x_ + pSize.x_ > pos.x_ - size.x_ &&
        pPos.x_ - pSize.x_ < pos.x_ + size.x_ &&
        pPos.y_ + pSize.y_ > pos.y_ - size.y_ &&
        pPos.y_ - pSize.y_ < pos.y_ + size.y_);
}

bool ShBoss::ShotHit(Vector2F sPos, Vector2F sSize)
{
    if (sPos.x_ + sSize.x_ > pos.x_ - hitSize.x_ &&
        sPos.x_ - sSize.x_ < pos.x_ + hitSize.x_ &&
        sPos.y_ + sSize.y_ > pos.y_ - hitSize.y_ &&
        sPos.y_ - sSize.y_ < pos.y_ + hitSize.y_)
    {
        --life;
        return true;
    }
    return false;
}

void ShBoss::Shot1(Vector2F sPos)
{
    Vector2F diff = player->GetPos() - sPos;

    float hy = hypotf(diff.x_, diff.y_);
    diff.x_ /= hy;
    diff.y_ /= hy;

    shooting->EnemyMakeShot(sPos, diff * 10.0f);
}

void ShBoss::Shot2(Vector2F sPos)
{
    for (int s = 0; s < 8; ++s)
    {
        float angle = DX_PI_F / 4 * s;

        Vector2F diff = { cosf(angle),sinf(angle) };

        shooting->EnemyMakeShot(sPos, diff * 10.0f);
    }
}

void ShBoss::Shot3(Vector2F sPos)
{
    shooting->EnemyMakeShot(sPos, { -10,0 });
}
