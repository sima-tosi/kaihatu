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

    int shotCnt;
    int targetCnt;

    Vector2F shotPos;
    std::list<Target> targets;
    int point;
};

