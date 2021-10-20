#include "AcPlayer.h"
#include "AcCamera.h"
#include "AcEnemy.h"
#include <DxLib.h>
#include <list>

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

void AcPlayer::Draw(void)
{
	float cameraPosX = mCamera->GetPos();

	DrawBox(pos.x_ - size.x_ - cameraPosX, pos.y_ - size.y_,
			pos.x_ + size.x_ - cameraPosX, pos.y_ + size.y_,
			0xffffff, true);
}

void AcPlayer::MapHitLR(int vec)
{
	Vector2F cPos = { pos.x_ + (size.x_ * vec),pos.y_ };
	Vector2F tPos = cPos;
	tPos.y_ -= size.y_;
	Vector2F dPos = cPos;
	dPos.y_ += size.y_;

	// どれかマップにあたる
	{
		// もどす
	}
}

void AcPlayer::MapHitUD(int vec)
{
	Vector2F cPos = { pos.x_,pos.y_ + (size.x_ * vec) };
	Vector2F lPos = cPos;
	lPos.x_ -= size.x_;
	Vector2F rPos = cPos;
	rPos.x_ += size.x_;

	// どれかマップにあたる
	{
		// もどす
		jump = 0.0f;
	}
}
