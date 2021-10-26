#include "ShEnemy.h"
#include <DxLib.h>
void ShEnemy::UpData(double delta)
{
    pos += vec;

    if (pos.x_ < 0 - size.x_ ||
        pos.y_ < 0 - size.y_ ||
        pos.y_ > 768 + size.y_)
    {
        kill = true;
    }
}

void ShEnemy::Draw(void)
{
    DrawBox(pos.x_ - size.x_, pos.y_ - size.y_,
        pos.x_ + size.x_, pos.y_ + size.y_,
        0xff0000, true);
}

bool ShEnemy::PlayerHit(Vector2F pPos, Vector2F pSize)
{
    return (pPos.x_ + pSize.x_ > pos.x_ - size.x_ &&
            pPos.x_ - pSize.x_ < pos.x_ + size.x_ &&
            pPos.y_ + pSize.y_ > pos.y_ - size.y_ &&
            pPos.y_ - pSize.y_ < pos.y_ + size.y_);
}

bool ShEnemy::ShotHit(Vector2F sPos, Vector2F sSize)
{
    if (sPos.x_ + sSize.x_ > pos.x_ - size.x_ &&
        sPos.x_ - sSize.x_ < pos.x_ + size.x_ &&
        sPos.y_ + sSize.y_ > pos.y_ - size.y_ &&
        sPos.y_ - sSize.y_ < pos.y_ + size.y_)
    {
        kill = true;
        return true;
    }
    return false;
}
