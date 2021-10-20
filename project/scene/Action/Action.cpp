#include "Action.h"
#include "AcPlayer.h"
#include "AcCamera.h"
#include "AcKuribo.h"
#include "AcDosunn.h"

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
	camera = new AcCamera(2560, 1280);
    player = std::make_unique<AcPlayer>(camera);

	UniEne enemy = std::make_unique<AcKuribo>(camera);
	enemys.push_back(std::move(enemy));

	limitTime = 120.0;
}

int Action::UpDate(KeyDate keyData,double delta)
{
	limitTime -= delta;

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
	player->Draw();
	for (auto& enemy : enemys)
	{
		enemy->Draw();
	}

	DrawFormatString(0, 20, 0xffffff, "%f", limitTime);
}