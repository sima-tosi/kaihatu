#pragma once
#include "Scene.h"
#include <chrono>

enum Glist
{
    ACTION,
    SHOOTING,
    PUZLE,
    SNAKE,
    GUN,
    MEMORY
};

struct GameList
{
    Glist name;
    int point;
};

class Game :
    public Scene
{
public:
    Game();
    ~Game();
    UniScene UpDate(UniScene scene, KeyDate keyData) override;
    virtual int UpDate(KeyDate keyData,double delta) { return -1; };
    virtual void Draw(void) override;

private:
    bool Init(void);
    void GraphDraw(void);
    void resultDraw(void);
    void TestUpDate(KeyDate keyData);

    int image[3];
    double resultTime = 0.0;
    double readyTime;
    double finishTime;

    std::unique_ptr <Game> game;
    bool play = false;
    int playCnt;
    GameList gameList[6];

    std::chrono::system_clock::time_point nowTime;
    std::chrono::system_clock::time_point oldTime;
};

