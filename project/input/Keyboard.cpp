#include <DxLib.h>
#include "Keyboard.h"

ContType Keyboard::GetContType(void)
{
	return ContType::Key;
}

bool Keyboard::SetUp(int no)
{
	inputTable = {
		{InputID::RIGHT	,KEY_INPUT_RIGHT	},
		{InputID::UP	,KEY_INPUT_UP		},
		{InputID::LEFT	,KEY_INPUT_LEFT		},
		{InputID::DOWN	,KEY_INPUT_DOWN		},
		{InputID::LROLL	,KEY_INPUT_Q		},
		{InputID::RROLL	,KEY_INPUT_E		},
		{InputID::SPACE	,KEY_INPUT_SPACE	},
	};
	return true;
}

void Keyboard::UpDate(void)
{
	GetHitKeyStateAll(keyStore.data());

	for (auto id : InputID())
	{
		data[id][Trg::Old] = data[id][Trg::Now];
  		data[id][Trg::Now] = keyStore[inputTable[id]];
	}
}
