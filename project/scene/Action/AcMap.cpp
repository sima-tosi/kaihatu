#include "AcMap.h"
#include "Action.h"
#include <DxLib.h>


AcMap::AcMap(Action* action)
{
	mAction = action;
	tmx = new TMXobj();
	tmx->LoadTMX("image/Action/Stage.tmx");
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

	int mapNo = tmx->GetMapData("block", mapPos);

	switch (mapNo)
	{
	case 0:
		return false;
		break;
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
		LimitBlock(pos, jumpVec);
		return OneMoveBlock(jumpVec);
	case 6:
	case 7:
		return true;
	case 8:
		ItemBlock(pos, jumpVec);
		return true;
		break;
	case 9:
		BreakBlock(pos, jumpVec);
		return true;
	case 10:
		return OneMoveBlock(jumpVec);
	case 11:
		mAction->ClearSet();
		return false;
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

int AcMap::GetMapData(std::string name, int x, int y)
{
	return tmx->GetMapData("enemy", x, y);
}

void AcMap::ScreenDraw(void)
{
	int befor = GetDrawScreen();

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

	SetDrawScreen(befor);
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
		tmx->ChangeChip("block", mapPos, 0);
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
			limitBlock.try_emplace(chipPos, 30);
		}
	}
}

void AcMap::ItemBlock(Vector2F pos, int vec)
{
	if (vec < 0)
	{
		Vector2 mapPos = { (int)pos.x_ / chipSize.x_,(int)pos.y_ / chipSize.y_ };
		tmx->ChangeChip("block", mapPos, 7);
		mAction->makeItem(mapPos ,chipSize);
		ScreenDraw();
	}
}

void AcMap::Draw(float cameraPos)
{
	DrawGraph(-cameraPos, 0, mapScreen, true);
}

void AcMap::UpData(void)
{
	for (auto& limit : limitBlock)
	{
		--limit.second;
		if (limit.second == 0)
		{
			Vector2 mapPos = { limit.first % mapSize.x_,limit.first / mapSize.x_ };
			tmx->ChangeChip("block", mapPos, tmx->GetMapData("block",mapPos.x_, mapPos.y_) - 1);
			limit.second = 30;
			ScreenDraw();
		}
	}
}
