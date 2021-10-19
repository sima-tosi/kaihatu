#pragma once
#include "../Game.h"
#include "../../Vector2.h"
#include <list>

enum class SHOTMODE
{
    NORMAL,
    TRIPLE,
    SIDE,
    PENETRA
};
enum class ENENYTYPE
{
    NORMAL,
    TRIPLE,
    RUSH,
    BOX,
    Boss
};

struct PLAYER
{
    Vector2F pos;
    SHOTMODE shot;
    double stayTime;
    double reStartTime;
};
struct SHOT
{
    Vector2F pos;
    Vector2F vec;
    bool penetra;
    bool kill;
};
struct ENEMY
{
    Vector2F pos;
    Vector2F vec;
    ENENYTYPE type;
    double stayTime;
    double time;
    int life;
    int shotCnt = 0;
};

class Shooting :
    public Game
{
public:
    Shooting();
    ~Shooting();
    int UpDate(KeyDate keyData,double delta);
    void Draw(void) override;
private:
    void Init(void);
    void PlayerMove(KeyDate keyData, double delta);
    void makeShot(void);

    void ShotMove(void);

    void EnemyMove(double delta);
    void RushMove(ENEMY& enemy);
    void NormalMove(ENEMY& enemy);
    void TripleMove(ENEMY& enemy);
    void BoxMove(ENEMY& enemy);
    void BossMove(ENEMY& enemy);

    void makeBossShot(ENEMY enemy);

    bool HitCheck(Vector2F mLU, Vector2F mRD, Vector2F yLU, Vector2F yRD);

    PLAYER player;
    std::list<SHOT> pShots;
    std::list<SHOT> eShots;
    std::list<ENEMY> enemys;

    void MOVEYOU(void);
    int nvr = 0;
};

