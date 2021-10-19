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

	UniEne enemy = std::make_unique<AcDosunn>(camera);
	enemys.push_back(std::move(enemy));
}

int Action::UpDate(KeyDate keyData,double delta)
{
	player->UpData(keyData, delta);
	camera->UpData(player->GetPos().x_);
	for (auto& enemy : enemys)
	{
		enemy->UpData(delta,player->GetPos());
		player->EnemyHit(enemy.get());
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
}