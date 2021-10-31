#pragma once
#include "../Game.h"
#include "../../Vector2.h"
#include <VECTOR>

enum DIR
{
    UP,
    LEFT,
    DOWN,
    RIGHT
};

struct Player
{
    Vector2 pos;
    DIR ent;
    DIR exit;
};
struct Item
{
    Vector2 pos;
    double limit;
    bool destor;
};

class Snake :
    public Game
{
public:
    Snake();
    ~Snake();
    int UpDate(KeyDate keyData,double delta) override;
    void Draw(void) override;
private:
    const double MAX_TIME = 20.0;

    void Init(void);
    void GetItem(void);
    void SetItem(void);
    void SetObs(void);
    void HitObs(int pos);

    std::vector<Player> body;
    std::vector<bool> obs;

    Item item;
    int itemCnt;
    bool turn;
    bool miss = false;
    int point;

    int screen;

    std::pair<DIR, DIR> moveDir;
    double count;
    double timeLimit;
    double breakTime;
};

