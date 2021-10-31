#pragma once
#include "ShEnemy.h"

class ShTreasure :
    public ShEnemy
{
public:
    ShTreasure(Shooting* _shooting, Vector2F _pos, int _image);
    ~ShTreasure();
    bool ShotHit(Vector2F sPos, Vector2F sSize)override;
public:
};

