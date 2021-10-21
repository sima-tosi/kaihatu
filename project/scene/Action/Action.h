#pragma once
#include "../Game.h"
#include "../../Vector2.h"
#include <list>

class AcPlayer;
class AcCamera;
class AcEnemy;
class AcMap;
class Action :
    public Game
{
public:
    Action();
    ~Action();
    int UpDate(KeyDate keyData, double delta);
    void Draw(void) override;

    void makeItem(Vector2 pos, Vector2 size);
private:
    void Init(void);

    std::unique_ptr<AcPlayer> player;
    std::list <std::unique_ptr<AcEnemy>> enemys;
    std::list<Vector2F> items;
    AcCamera* camera;
    AcMap* map;

    double limitTime;
};

using UniEne = std::unique_ptr<AcEnemy>;