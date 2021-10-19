#include "Pad.h"
#include <DxLib.h>

ContType Pad::GetContType(void)
{
	return ContType::Key;
}

bool Pad::SetUp(int no)
{
	inputTable = {
		{InputID::RIGHT	,PAD_INPUT_RIGHT},
		{InputID::UP	,PAD_INPUT_UP},
		{InputID::LEFT	,PAD_INPUT_LEFT},
		{InputID::DOWN	,PAD_INPUT_DOWN},
		{InputID::LROLL	,PAD_INPUT_Y},
		{InputID::RROLL	,PAD_INPUT_Z},
		{InputID::SPACE ,PAD_INPUT_A},
	};
	return true;
}

void Pad::UpDate(void)
{
	int state = GetJoypadInputState(DX_INPUT_PAD1);
	for (auto id : InputID())
	{
		data[id][Trg::Old] = data[id][Trg::Now];
		data[id][Trg::Now] = (state & inputTable[id]);
	}
}