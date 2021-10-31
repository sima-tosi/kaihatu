#pragma once
#include "ShEnemy.h"
#include "../ShPlayer.h"

class ShItem :
    public ShEnemy
{
public:
    ShItem(ShPlayer* _player, Vector2F _pos, int _image,int iNo);
    ~ShItem();

    bool PlayerHit(Vector2F pPos, Vector2F pSize) override;
    bool ShotHit(Vector2F sPos, Vector2F sSize) { return false; };
public:
    ShPlayer* player;
    ShotMode mode;
};

