#include "ShCurve.h"
#include "../Shooting.h"
#include <math.h>

ShCurve::ShCurve(Shooting* _shooting, Vector2F _pos)
{
    scene = _shooting;
    pos = _pos;
    startPos = pos.y_;
    vec = { -5.0,0 };
}

ShCurve::~ShCurve()
{
}

void ShCurve::UpData(double delta)
{
    shotTime -= delta;
    time += delta;

    pos.x_ += vec.x_;
    pos.y_ = (sin(time * 2) * 300) + startPos;

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
        Vector2F sVec = {-12.5,0};

        scene->EnemyMakeShot(sPos,sVec);
    }
}
