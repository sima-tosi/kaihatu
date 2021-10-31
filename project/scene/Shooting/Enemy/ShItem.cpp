#include "ShItem.h"
#include "../ShPlayer.h"

ShItem::ShItem(ShPlayer* _player, Vector2F _pos, int _image,int iNo)
{
    player = _player;
    pos = _pos;
    vec = { -3.0,0 };
    image = _image;

    mode = (ShotMode)(iNo);
}

ShItem::~ShItem()
{
}

bool ShItem::PlayerHit(Vector2F pPos, Vector2F pSize)
{
    if (pPos.x_ + pSize.x_ > pos.x_ - size.x_ &&
        pPos.x_ - pSize.x_ < pos.x_ + size.x_ &&
        pPos.y_ + pSize.y_ > pos.y_ - size.y_ &&
        pPos.y_ - pSize.y_ < pos.y_ + size.y_)
    {
        player->GetItem(mode);
        kill = true;
    }
    return false;
}
