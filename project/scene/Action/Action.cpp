#include "Action.h"
#include "AcPlayer.h"
#include "AcCamera.h"
#include "Enemy/AcKuribo.h"
#include "Enemy/AcDosunn.h"
#include "Enemy/AcTogezo.h"
#include "AcMap.h"
#include "Enemy/AcItem.h"
#include "../../Vector2.h"
#include <DxLib.h>

Action::Action()
{
    Init();
}
Action::~Action()
{
	delete camera;
}
void Action::Init(void)
{
	map = new AcMap(&(*this));
	camera = new AcCamera(map->GetMapSize().x_ * map->GetChipSize().x_, 1024);
    player = std::make_unique<AcPlayer>(camera,map);
	SetEnemy();

	limitTime = 120.0;
	clear = false;

	GameScreen = MakeScreen(1024, 704);
}

void Action::SetEnemy(void)
{
	Vector2 chip = map->GetChipSize();
	for (int y = 0; y < map->GetMapSize().y_; ++y)
	{
		for (int x = 0; x < map->GetMapSize().x_; ++x)
		{
			Vector2F pos = { (float)(x * chip.x_),(float)(y * chip.y_) };
			pos += {32.0f, 32.0f};

			UniEne enemy;
			switch (map->GetMapData("enemy", x, y))
			{
			case 0:
				break;
			case 12:
				enemy = std::make_unique<AcKuribo>(camera, map, pos);
				enemys.push_back(std::move(enemy));
				break;
			case 13:
				enemy = std::make_unique<AcTogezo>(camera, map, pos);
				enemys.push_back(std::move(enemy));
				break;
			case 14:
				enemy = std::make_unique<AcDosunn>(camera, map, pos);
				enemys.push_back(std::move(enemy));
				break;
			}
		}
	}
}

int Action::UpDate(KeyDate keyData,double delta)
{
	limitTime -= delta;
	map->UpData();

	player->UpData(keyData, delta);

	camera->UpData(player->GetPos().x_);

	for (auto& enemy : enemys)
	{
		enemy->UpData(delta,player->GetPos());
		player = enemy->PlayerDeath(std::move(player));
	}

	auto o = std::remove_if(enemys.begin(), enemys.end(), [](UniEne& enemy) {return enemy->GetKill(); });
	enemys.erase(o, enemys.end());

	if (player->GetKill() || limitTime < 0.0)
	{
		return 0;
	}
	if (clear) return 1;
	return -1;
}

void Action::Draw(void)
{
	DrawString(0, 0, "ActionScene", 0xffffff);
	
	SetDrawScreen(GameScreen);
	ClsDrawScreen();

	map->Draw(camera->GetPos());
	player->Draw();
	for (auto& enemy : enemys)
	{
		enemy->Draw();
	}

	SetDrawScreen(DX_SCREEN_BACK);

	DrawGraph(0, 64, GameScreen, true);

	DrawFormatString(0, 20, 0xffffff, "%f", limitTime);
}

void Action::makeItem(Vector2 pos, Vector2 size)
{
	Vector2F iPos = { (float)(pos.x_ * size.x_),(float)(pos.y_ * size.y_) };
	iPos.x_ += size.x_ / 2;
	iPos.y_ -= size.y_ / 2;

	UniEne enemy = std::make_unique<AcItem>(camera, map,iPos);
	enemys.push_back(std::move(enemy));
}
