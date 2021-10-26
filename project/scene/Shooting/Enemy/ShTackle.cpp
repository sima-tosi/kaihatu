#include "ShTackle.h"
#include "../ShPlayer.h"
ShTackle::ShTackle(ShPlayer* _player, Vector2F _pos)
{
    player = _player;
    pos = _pos;
    vec = { -9.0f,0 };
}

ShTackle::~ShTackle()
{
}

void ShTackle::UpData(double delta)
{
    int oldPos = pos.x_;
    pos += vec;

    if (pos.x_ < 0 - size.x_ ||
        pos.y_ < 0 - size.y_ ||
        pos.y_ > 768 + size.y_)
    {
        kill = true;
    }

    if (vec.y_ == 0)
    {
        Vector2F pPos = player->GetPos();
        if (oldPos >= pPos.x_ &&
            pos.x_ <= pPos.x_)
        {
            if (pos.y_ > 768 / 2)
            {
                vec.y_ = vec.x_;
            }
            else
            {
                vec.y_ = -vec.x_;
            }
            
            vec.x_ = 0;
        }
    }
}
