#include "ShTriple.h"
#include "../Shooting.h"

ShTriple::ShTriple(Shooting* _shooting, Vector2F _pos, int _image)
{
	scene = _shooting;
    pos = _pos;
    vec = { -7,0 };
    image = _image;
}

ShTriple::~ShTriple()
{
}

void ShTriple::UpData(double delta)
{
    pos += vec;
    shotTime -= delta;

    if (pos.x_ < 0 - size.x_ ||
        pos.y_ < 0 - size.y_ ||
        pos.y_ > 768 + size.y_)
    {
        kill = true;
    }

    if (shotTime <= 0)
    {
        shotTime = 1.0;

        Vector2F sPos = pos;
        sPos.x_ -= size.x_;
        Vector2F sVec = { -12.5,0 };
        scene->EnemyMakeShot(sPos, sVec);
        sVec.y_ = -10;
        scene->EnemyMakeShot(sPos, sVec);
        sVec.y_ = 10;
        scene->EnemyMakeShot(sPos, sVec);
    }
}
