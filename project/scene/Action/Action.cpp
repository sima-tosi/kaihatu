#include "Action.h"
#include "AcPlayer.h"
#include "AcCamera.h"
#include "AcKuribo.h"
#include "AcDosunn.h"
#include "AcMap.h"
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
	camera = new AcCamera(2560, 720);
    player = std::make_unique<AcPlayer>(camera,map);
	//UniEne enemy = std::make_unique<AcKuribo>(camera);
	//enemys.push_back(std::move(enemy));

	limitTime = 120.0;
}

int Action::UpDate(KeyDate keyData,double delta)
{
	/*limitTime -= delta;*/

	player->UpData(keyData, delta);

	camera->UpData(player->GetPos().x_);

	for (auto& enemy : enemys)
	{
		enemy->UpData(delta,player->GetPos());
		if (enemy->PlayerDeath(player->GetPos(), player->GetSize()))
		{
			player->Death();
		}
	}

	auto o = std::remove_if(enemys.begin(), enemys.end(), [](UniEne& enemy) {return enemy->GetKill(); });
	enemys.erase(o, enemys.end());

	if (player->GetKill() || limitTime < 0.0)
	{
		return 0;
	}

	return -1;
}

void Action::Draw(void)
{
	DrawString(0, 0, "ActionScene", 0xffffff);
	map->Draw(camera->GetPos());
	player->Draw();
	for (auto& enemy : enemys)
	{
		enemy->Draw();
	}
	for (auto& item : items)
	{
		DrawBox(item.x_ - 16 - camera->GetPos(), item.y_ - 16,
			item.x_ + 16 - camera->GetPos(), item.y_ + 16,
			0xffff00, true);
	}
	DrawFormatString(0, 20, 0xffffff, "%f", limitTime);
}

void Action::makeItem(Vector2 pos, Vector2 size)
{
	Vector2F iPos = { (float)(pos.x_ * size.x_),(float)(pos.y_ * size.y_) };
	iPos.x_ += size.x_ / 2;
	iPos.y_ -= size.y_ / 2;
	items.emplace_back(iPos);
}
