#include "ShPlayer.h"
#include "Shooting.h"
#include "../../input/Control.h"
#include <DxLib.h>

ShPlayer::ShPlayer(Shooting* _shooting)
{
    shooting = _shooting;
    shotTime = 0.0;
    Init();
}

ShPlayer::~ShPlayer()
{
}

void ShPlayer::Init(void)
{
    mode = ShotMode::Non;
    size = { 32,32 };
    hitSize = { 8,8 };
    pos = { 132,384 };
}

void ShPlayer::UpDate(KeyDate keyData, double delta)
{
    if (killTime > 0.0) killTime -= delta;
    shotTime -= delta;

    if (keyData[InputID::UP][Trg::Now])
    {
        pos.y_ -= SPEED;
    }
    if (keyData[InputID::DOWN][Trg::Now])
    {
        pos.y_ += SPEED;
    }
    if (keyData[InputID::LEFT][Trg::Now])
    {
        pos.x_ -= SPEED;
    }
    if (keyData[InputID::RIGHT][Trg::Now])
    {
        pos.x_ += SPEED;
    }

    if (killTime <= 0.0)
    {
        if (keyData[InputID::SPACE][Trg::Now])
        {
            if (shotTime <= 0.0)
            {
                switch (mode)
                {
                case ShotMode::Non:
                    NonMake();
                    break;
                case ShotMode::Triple:
                    TripleMake();
                    break;
                case ShotMode::Side:
                    SideMake();
                    break;
                case ShotMode::Quick:
                    QuickMake();
                    break;
                default:
                    break;
                }
            }
        }
    }
}

void ShPlayer::Draw(void)
{
    if (killTime <= 0.0)
    {
        DrawBox(pos.x_ - size.x_, pos.y_ - size.y_,
            pos.x_ + size.x_, pos.y_ + size.y_,
            0xffffff, true);
    }
    else
    {
        int frame = killTime / (1.0 / 60);
        if (frame / 10 % 2 == 0)
        {
            DrawBox(pos.x_ - size.x_, pos.y_ - size.y_,
                pos.x_ + size.x_, pos.y_ + size.y_,
                0xff0000, true);
        }
    }
}

void ShPlayer::Kill(void)
{
    if (killTime <= 0.0)
    {
        shooting->ScoreDown();
        kill = true;
        killTime = 3.0;
        mode = ShotMode::Non;
    }
}

bool ShPlayer::ShotHit(Vector2F sPos, Vector2F sSize)
{
    if (killTime <= 0.0)
    {
        if (sPos.x_ + sSize.x_ > pos.x_ - hitSize.x_ &&
            sPos.x_ - sSize.x_ < pos.x_ + hitSize.x_ &&
            sPos.y_ + sSize.y_ > pos.y_ - hitSize.y_ &&
            sPos.y_ - sSize.y_ < pos.y_ + hitSize.y_)
        {
            Kill();
            return true;
        }
    }

    return false;
}

void ShPlayer::GetItem(ShotMode Item)
{
    mode = Item;
}

void ShPlayer::NonMake(void)
{
    shotTime = SHOT_TIME;
    Vector2F sPos = pos;
    sPos.x_ += size.x_;
    Vector2F sVec = { 12.5,0 };
    shooting->PlayerMakeShot(sPos, sVec);
}

void ShPlayer::TripleMake(void)
{
    shotTime = SHOT_TIME;
    Vector2F sPos = pos;

    sPos.x_ += size.x_;
    sPos.y_ += size.y_;
    Vector2F sVec = { 10.0,10.0 };
    shooting->PlayerMakeShot(sPos, sVec);

    sPos.y_ = pos.y_ - size.y_;
    sVec = { 10.0,-10.0 };
    shooting->PlayerMakeShot(sPos, sVec);

    sPos = pos;
    sPos.x_ -= size.x_;
    sVec = { -12.5,0 };
    shooting->PlayerMakeShot(sPos, sVec);
}

void ShPlayer::SideMake(void)
{
    shotTime = SHOT_TIME;
    Vector2F sPos = pos;
    sPos.y_ += size.y_;
    Vector2F sVec = { 12.5,0 };
    shooting->PlayerMakeShot(sPos, sVec);
    sPos.y_ = pos.y_ - size.y_;
    shooting->PlayerMakeShot(sPos, sVec);
}

void ShPlayer::QuickMake(void)
{
    shotTime = SHOT_TIME / 3;
    Vector2F sPos = pos;
    sPos.x_ += size.x_;
    Vector2F sVec = { 12.5,0 };
    shooting->PlayerMakeShot(sPos, sVec);
}
