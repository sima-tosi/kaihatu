#include "AcMap.h"
#include <DxLib.h>
AcMap::AcMap()
{
	// tmx“Ç‚Ýž‚Ý
	Init();
}

void AcMap::Init(void)
{
	Vector2 screenSize = mapSize * chipSize;
	mapScreen = MakeScreen(screenSize.x_, screenSize.y_);
}

bool AcMap::HitMap(Vector2 pos, float jumpVec)
{
	Vector2 mapPos = pos / chipSize;

	if (map[mapPos.y_ * mapSize.x_ + mapPos.x_] != 0)
	{
		return true;
	}

	return false;
}

void AcMap::ScreenDraw(void)
{
	SetDrawScreen(mapScreen);
	ClsDrawScreen();

	int cnt = 0;
	for (auto chip : map)
	{
		if (chip > 0)
		{
			DrawGraph(cnt / mapSize.x_, cnt / mapSize.x_,
					 mapImage[chip - 1], true);
		}
		++cnt;
	}

	SetDrawScreen(DX_SCREEN_BACK);
}

void AcMap::Draw(Vector2F cameraPos)
{
	DrawGraph(-cameraPos.x_, -cameraPos.y_, mapScreen, true);
}
