#include "ShTreasure.h"
#include "../Shooting.h"

ShTreasure::ShTreasure(Shooting* _shooting, Vector2F _pos, int _image)
{
	scene = _shooting;
    pos = _pos;
    vec = { -3,0 };
    image = _image;
}

ShTreasure::~ShTreasure()
{
}

bool ShTreasure::ShotHit(Vector2F sPos, Vector2F sSize)
{
    if (sPos.x_ + sSize.x_ > pos.x_ - size.x_ &&
        sPos.x_ - sSize.x_ < pos.x_ + size.x_ &&
        sPos.y_ + sSize.y_ > pos.y_ - size.y_ &&
        sPos.y_ - sSize.y_ < pos.y_ + size.y_)
    {
        kill = true;
        scene->SpawnItem(pos);
        return true;
    }
    return false;
}
