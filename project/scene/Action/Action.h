#pragma once
#include "../Game.h"
#include "../../Vector2.h"
#include <list>
#include<vector>
#include<map>

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
    void ClearSet(void) { clear = true; };
private:
    void Init(void);
    void SetEnemy(void);

    bool clear;
    int GameScreen;

    std::unique_ptr<AcPlayer> player;
    std::list <std::unique_ptr<AcEnemy>> enemys;
    std::vector<int> enemyImage;
    AcCamera* camera;
    AcMap* map;

    double limitTime;
};

using UniEne = std::unique_ptr<AcEnemy>;