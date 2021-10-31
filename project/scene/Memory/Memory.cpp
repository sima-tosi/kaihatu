#include "Memory.h"
#include <DxLib.h>

Memory::Memory()
{
    Init();
}
Memory::~Memory()
{
    
}

void Memory::Init(void)
{
    CHOICE choice;
    choice.image = 0xff0000;
    choices.push_back(choice);
    choice.image = 0x00ff00;
    choices.push_back(choice);
    choice.image = 0x0000ff;
    choices.push_back(choice);
    choice.image = 0xffffff;
    choices.push_back(choice);

    level = 2;
    miss = false;
    mode = MODE::CHECK;
}

void Memory::SetLevel(void)
{
    ++level;
    
    if (level > 28) miss = true;

    mode = MODE::MEMORY;
    check.clear();

    answer.clear();
    for (int a = 0; a < level; ++a)
    {
        answer.push_back(rand() % 4);
    }
    limit = 1.0;

    number = 0;
}

int Memory::UpDate(KeyDate keyData, double delta)
{
    switch (mode)
    {
    case Memory::MEMORY:
        MemoryUpData();
        break;
    case Memory::RES:
        ResUpData(keyData);
        break;
    case Memory::CHECK:
        CheckUpData();
        break;
    default:
        break;
    }

    limit -= delta;
    if (miss && limit < 0.0) return (level - 3) * 10;
    return -1;
}
void Memory::MemoryUpData(void)
{
    if (limit <= 0.0)
    {
        if (limit <= -0.1)
        {
            if (number < level - 1)
            {
                ++number;
                limit = 1.0;
            }
            else mode = MODE::RES;
        }
    }
}
void Memory::ResUpData(KeyDate keyData)
{
    if (keyData[InputID::UP][Trg::Now] &&
        !keyData[InputID::UP][Trg::Old])
    {
        check.push_back(0);
    }
    else if (keyData[InputID::DOWN][Trg::Now] &&
        !keyData[InputID::DOWN][Trg::Old])
    {
        check.push_back(2);
    }
    else if (keyData[InputID::LEFT][Trg::Now] &&
        !keyData[InputID::LEFT][Trg::Old])
    {
        check.push_back(1);
    }
    else if (keyData[InputID::RIGHT][Trg::Now] &&
        !keyData[InputID::RIGHT][Trg::Old])
    {
        check.push_back(3);
    }

    if (check.size() == answer.size())
    {
        mode = MODE::CHECK;
        limit = 1.5;

        for (int ni = 0; ni < answer.size(); ++ni)
        {
            if (answer[ni] != check[ni])
            {
                miss = true;
                // ‰¹
            }
        }
    }
}
void Memory::CheckUpData(void)
{
    if (limit < 0.0)
    {
        if (!miss) SetLevel();
    }
}

void Memory::Draw(void)
{
    DrawString(0, 0, "MemoryScene", 0xffffff);

    switch (mode)
    {
    case Memory::MEMORY:
        MemoryDraw();
        break;
    case Memory::RES:
        ResDraw();
        break;
    case Memory::CHECK:
        CheckDraw();
        break;
    default:
        break;
    }
}
void Memory::MemoryDraw(void)
{
    if (limit > 0.0)
    {
        DrawBox(100, 100, 500, 500, choices[answer[number]].image, true);
    }
}
void Memory::ResDraw(void)
{
    int cnt = 0;
    for (auto oao : check)
    {
        DrawBox(110 * (cnt % 9), 110 * (cnt / 9) + 50,
            110 * (cnt % 9) + 100, 110 * (cnt / 9) + 150,
            choices[oao].image, true);
        ++cnt;
    }
    for (cnt; cnt < answer.size(); ++cnt)
    {
        DrawBox(110 * (cnt % 9), 110 * (cnt / 9) + 50,
            110 * (cnt % 9) + 100, 110 * (cnt / 9) + 150,
            0x888888, true);
    }

    DrawBox(512 - 32, (768 / 4) * 3 - 32 - 64,
            512 + 32, (768 / 4) * 3 + 32 - 64,
            choices[0].image, true);
    DrawBox(512 - 32 - 64, (768 / 4) * 3 - 32,
            512 + 32 - 64, (768 / 4) * 3 + 32,
            choices[1].image, true);
    DrawBox(512 - 32, (768 / 4) * 3 - 32 + 64,
            512 + 32, (768 / 4) * 3 + 32 + 64,
            choices[2].image, true);
    DrawBox(512 - 32 + 64, (768 / 4) * 3 - 32,
            512 + 32 + 64, (768 / 4) * 3 + 32,
            choices[3].image, true);
}
void Memory::CheckDraw(void)
{
    int cnt = 0;
    for (auto oao : check)
    {
        DrawBox(110 * (cnt % 9), 110 * (cnt / 9) + 50,
            110 * (cnt % 9) + 100, 110 * (cnt / 9) + 150,
            choices[oao].image, true);
        ++cnt;
    }
    cnt = 0;

    for (auto oao : answer)
    {
        DrawBox(110 * (cnt % 9), 110 * (cnt / 9) + 384 + 50,
            110 * (cnt % 9) + 100, 110 * (cnt / 9) + 384 + 150,
            choices[oao].image, true);
        ++cnt;
    }
}