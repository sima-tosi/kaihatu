#include "ShEnemy.h"
#include <DxLib.h>
void ShEnemy::UpData(double delta)
{
    pos += vec;
}

void ShEnemy::Draw(void)
{
    DrawBox(pos.x_ - size.x_, pos.y_ - size.y_,
        pos.x_ + size.x_, pos.y_ + size.y_,
        0xff0000, true);
}

bool ShEnemy::PlayerHit(Vector2F pPos, Vector2F pSize)
{
    if()
}

void ShEnemy::ShotHit(Vector2F pos, Vector2F size)
{
}
