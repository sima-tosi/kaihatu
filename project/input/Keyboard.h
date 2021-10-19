#pragma once

#include<map>
#include<array>
#include"Control.h"
#include"InputID.h"

class Keyboard :
    public Control
{
public:
    ContType GetContType(void) override;
    bool SetUp(int no) override;
    void UpDate(void) override;

private:
    std::array<char, 256> keyStore = { NULL };
    std::map<InputID, int> inputTable;
};

