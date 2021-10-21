#include "AcMap.h"
#include "Action.h"
#include <DxLib.h>


AcMap::AcMap(Action* action)
{
	mAction = action;
	tmx = new TMXobj();
	tmx->LoadTMX("image/testMap.tmx");
	Init();
}

AcMap::~AcMap()
{
	delete tmx;
}

void AcMap::Init(void)
{
	mapSize = tmx->GetWorldArea();
	chipSize = tmx->GetTileSize();

	Vector2 screenSize = mapSize * chipSize;
	mapScreen = MakeScreen(screenSize.x_, screenSize.y_);
	ScreenDraw();
}

bool AcMap::HitMap(Vector2F pos, int jumpVec)
{
	Vector2 mapPos = { (int)pos.x_, (int)pos.y_};

	int mapNo = tmx->GetMapData("test", mapPos);

	switch (mapNo)
	{
	case 0:
		return false;
		break;
	case 5:
		ItemBlock(pos, jumpVec);
		return true;
		break;
	case 3:
		BreakBlock(pos, jumpVec);
	case 1:
	case 4:
		return true;
		break;
	case 6:
		LimitBlock(pos, jumpVec);
	case 2:
		return OneMoveBlock(jumpVec);
	default:
		break;

	}

	return false;
}

Vector2 AcMap::BackPos(Vector2F pos,int vec)
{
	Vector2 mapPos = { (int)pos.x_, (int)pos.y_ };

	mapPos /= tmx->GetTileSize();

	if (vec == - 1)
	{
		++mapPos.x_;
		++mapPos.y_;
	}

	return mapPos * chipSize;
}

void AcMap::ScreenDraw(void)
{
	SetDrawScreen(mapScreen);
	ClsDrawScreen();

	auto mapImage = tmx->GetImage();
	for (auto lays : tmx->GetMapData())
	{
		int cnt = 0;
		for (auto chip : lays.second)
		{
			if (chip > 0)
			{
				DrawGraph((cnt % mapSize.x_) * chipSize.x_, (cnt / mapSize.x_) * chipSize.y_,
					mapImage[chip- 1], true);
			}
			++cnt;
		}
	}

	SetDrawScreen(DX_SCREEN_BACK);
}

bool AcMap::OneMoveBlock(int vec)
{
	return vec > 0;
}

void AcMap::BreakBlock(Vector2F pos, int vec)
{
	if (vec < 0)
	{
		Vector2 mapPos = { (int)pos.x_ / chipSize.x_,(int)pos.y_ / chipSize.y_ };
		tmx->ChangeChip("test", mapPos, 0);
		ScreenDraw();
	}
}

void AcMap::LimitBlock(Vector2F pos, int vec)
{
	if (vec > 0)
	{
		Vector2 mapPos = { (int)pos.x_,(int)pos.y_ };
		mapPos /= chipSize;
		int chipPos = mapPos.y_ * mapSize.x_ + mapPos.x_;
		if (limitBlock.count(chipPos) == 0)
		{
			limitBlock.try_emplace(chipPos, 300);
		}
		else
		{
			--limitBlock[chipPos];
			if (limitBlock[chipPos] == 0)
			{
				tmx->ChangeChip("test", mapPos, 0);
				ScreenDraw();
			}
		}
	}
}

void AcMap::ItemBlock(Vector2F pos, int vec)
{
	if (vec < 0)
	{
		Vector2 mapPos = { (int)pos.x_ / chipSize.x_,(int)pos.y_ / chipSize.y_ };
		tmx->ChangeChip("test", mapPos, 4);
		mAction->makeItem(mapPos ,chipSize);
		ScreenDraw();
	}
}

void AcMap::Draw(float cameraPos)
{
	DrawGraph(-cameraPos, 0, mapScreen, true);
}
