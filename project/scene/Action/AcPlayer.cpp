#include "AcPlayer.h"
#include "AcCamera.h"
#include "AcEnemy.h"
#include <DxLib.h>

AcPlayer::AcPlayer(AcCamera* camera)
{
	mCamera = camera;
	Init();
}
void AcPlayer::Init(void)
{
	size = { 32,64 };
	pos = { 50,100 };
	jump = 0;
}

void AcPlayer::UpData(KeyDate keyData, double delta)
{
	if (keyData[InputID::LEFT][Trg::Now])
	{
		pos.x_ -= 10;
	}
	if (keyData[InputID::RIGHT][Trg::Now])
	{
		pos.x_ += 10;
	}
	if (keyData[InputID::UP][Trg::Now])
	{
		if(jump == 0.0f) jump += 20;
	}

	float cameraPosX = mCamera->GetPos();
	if (cameraPosX + size.x_ > pos.x_ )
	{
		pos.x_ = cameraPosX + size.x_;
	}
	else if	(cameraPosX - size.x_ + 1280 < pos.x_)
	{
		pos.x_ = cameraPosX - size.x_ + 1280;
	}

	jump -= 0.5;
	pos.y_ -= jump;

	if (pos.y_ > 720 - size.y_)
	{
		pos.y_ = 720 - size.y_;
		jump = 0.0f;
	}
}

bool AcPlayer::EnemyHit(AcEnemy* enemy)
{
	Vector2F ePos = enemy->GetPos();
	Vector2 eSize = enemy->GetSize();

	if (pos.x_ + size.x_ > ePos.x_ - eSize.x_ &&
		pos.x_ - size.x_ < ePos.x_ + eSize.x_ &&
		pos.y_ + size.y_ > ePos.y_ - eSize.y_ &&
		pos.y_ - size.y_ < ePos.y_ + eSize.y_)
	{

		return true;
	}
	return false;
}

void AcPlayer::Draw(void)
{
	float cameraPosX = mCamera->GetPos();

	DrawBox(pos.x_ - size.x_ - cameraPosX, pos.y_ - size.y_,
			pos.x_ + size.x_ - cameraPosX, pos.y_ + size.y_,
			0xffffff, true);
}
