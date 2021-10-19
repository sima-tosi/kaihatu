#pragma once
#include "../Game.h"
#include <list>

class AcPlayer;
class AcCamera;
class AcEnemy;
class Action :
    public Game
{
public:
    Action();
    ~Action();
    int UpDate(KeyDate keyData, double delta);
    void Draw(void) override;
private:
    void Init(void);
    std::unique_ptr<AcPlayer> player;
    std::list <std::unique_ptr<AcEnemy>> enemys;
    AcCamera* camera;
};

using UniEne = std::unique_ptr<AcEnemy>;