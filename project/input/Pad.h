#pragma once

#include<map>
#include<array>
#include"Control.h"
#include"InputID.h"

class Pad :
	public Control
{
public:
    ContType GetContType(void) override;
    bool SetUp(int no) override;
    void UpDate(void) override;

private:
    int padType = NULL;
    std::map<InputID, int> inputTable;
};

