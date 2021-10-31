#pragma once
#include "../Game.h"
#include "../../Vector2.h"
#include <list>
struct Target
{
    Vector2F pos;
    Vector2F vec;
    int size;
    bool life;
};
struct HitTarget
{
    Vector2F pos;
    int size;
    double time;
};
class Gun :
    public Game
{
public:
    Gun();
    ~Gun();
    int UpDate(KeyDate keyData, double delta);
    void Draw(void) override;
private:
    void Init(void);
    void SetTarget(void);

    int targetImage;
    int bangImage;
    int gunImage;

    int shotCnt;
    int targetCnt;
    double downTime;

    Vector2F shotPos;
    std::list<Target> targets;
    std::list<HitTarget> hTargets;
    int point;
};

