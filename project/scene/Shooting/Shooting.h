#pragma once
#include "../Game.h"
#include "../../Vector2.h"
#include <list>
#include<vector>

enum class EnemyType
{
    Curve,
    Triple,
    Tackle,
    Treasure,
};

struct EnemyVecData
{
    Vector2F pos;
    EnemyType type;
    double time;
};

class ShPlayer;
class ShShot;
class ShEnemy;
class ShBoss;
class Shooting :
    public Game
{
public:
    Shooting();
    ~Shooting();
    int UpDate(KeyDate keyData,double delta);
    void Draw(void) override;
    void EnemyMakeShot(Vector2F pos, Vector2F vec);
    void PlayerMakeShot(Vector2F pos, Vector2F vec);
    void SpawnItem(Vector2F ePos);
private:
    void Init(void);
    void SetEnemyVec(void);
    void Stage(void);

    std::vector<EnemyVecData> enemyVec;
    int spawnCnt;

    double time;
    bool Boss = false;

    ShPlayer* player;
    std::unique_ptr<ShBoss> boss;
    std::list<std::unique_ptr<ShShot>> pShots;
    std::list<std::unique_ptr<ShShot>> eShots;
    std::list<std::unique_ptr<ShEnemy>> enemys;
};