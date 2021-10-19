#pragma once
#include "../Game.h"
#include <vector>
#include <map>
#include <functional>

struct CHOICE
{
    int image;
};

class Memory :
    public Game
{
public:
    Memory();
    ~Memory();
    int UpDate(KeyDate keyData, double delta);
    void Draw(void) override;
private:
    enum MODE
    {
        MEMORY,
        RES,
        CHECK
    };

    void Init(void);
    void SetLevel(void);

    void MemoryUpData(void);
    void ResUpData(KeyDate keyData);
    void CheckUpData(void);
    void MemoryDraw(void);
    void ResDraw(void);
    void CheckDraw(void);

    double limit;

    MODE mode;
    std::vector<CHOICE> choices;
    std::vector<int> answer;
    std::vector<int> check;
    int number;
    int level;
    bool miss;
};

