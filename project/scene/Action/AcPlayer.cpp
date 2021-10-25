#include "AcPlayer.h"
#include "AcCamera.h"
#include "Enemy/AcEnemy.h"
#include "AcMap.h"
#include <DxLib.h>
#include <list>

AcPlayer::AcPlayer(AcCamera* camera,AcMap* map)
{
	mCamera = camera;
	mMap = map;
	Init();
}
void AcPlayer::Init(void)
{
	size = { 32,64 };
	pos = { 50,100 };
	jump = 0;
	jumpFlag = false;
	item = false;
	muteki = 0.0;
}

void AcPlayer::UpData(KeyDate keyData, double delta)
{
	muteki -= delta;

	int moveVec = 0;
	if (keyData[InputID::LEFT][Trg::Now])
	{
		pos.x_ -= 10;
		moveVec -= 1;
	}
	if (keyData[InputID::RIGHT][Trg::Now])
	{
		pos.x_ += 10;
		moveVec += 1;
	}

	float cameraPosX = mCamera->GetPos();
	if (cameraPosX + size.x_ > pos.x_)
	{
		pos.x_ = cameraPosX + size.x_;
	}
	else if (cameraPosX - size.x_ + 1280 < pos.x_)
	{
		pos.x_ = cameraPosX - size.x_ + 1280;
	}

	if (moveVec != 0)
	{
		MapHitLR(moveVec);
	}

	if (keyData[InputID::UP][Trg::Now])
	{
		if (jumpFlag)
		{
			jump += 20;
			jumpFlag = false;
		}
	}

	jump -= 0.5;
	pos.y_ -= jump;

	moveVec = jump < 0 ? 1 : -1;
	MapHitUD(moveVec);

	//if (pos.y_ > 720 - size.y_)
	//{
	//	pos.y_ = 720 - size.y_;
	//	jump = 0.0f;
	//}
}

void AcPlayer::Draw(void)
{
	float cameraPosX = mCamera->GetPos();

	DrawBox(pos.x_ - size.x_ - cameraPosX, pos.y_ - size.y_,
			pos.x_ + size.x_ - cameraPosX, pos.y_ + size.y_,
			0xffffff, item);

}
void AcPlayer::Death(void)
{
	if (muteki <= 0.0)
	{
		if (item)
		{
			item = false;
			muteki = 2.0;
		}
		else
		{
			kill = true;
		}
	}
}
void AcPlayer::MapHitLR(int vec)
{
	Vector2F cPos = { pos.x_ + (size.x_ * vec),pos.y_ };
	Vector2F tPos = cPos;
	tPos.y_ -= size.y_;
	Vector2F dPos = cPos;
	dPos.y_ += size.y_;

	if (mMap->HitMap(cPos, 0) || mMap->HitMap(tPos, 0) || mMap->HitMap(dPos, 0))
	{
		int cPosX = mMap->BackPos(cPos, vec).x_;
		pos.x_ = cPosX - (size.x_ * vec);
	}
}

void AcPlayer::MapHitUD(int vec)
{
	Vector2F cPos = { pos.x_,pos.y_ + (size.y_ * vec) };
	Vector2F lPos = cPos;
	lPos.x_ -= size.x_;
	Vector2F rPos = cPos;
	rPos.x_ += size.x_;

	bool stop = false;
	stop = mMap->HitMap(cPos, vec) || stop;
	stop = mMap->HitMap(lPos, vec) || stop;
	stop = mMap->HitMap(rPos, vec) || stop;

	if (stop)
	{
		int cPosY = mMap->BackPos(cPos, vec).y_;
		pos.y_ = cPosY - (size.y_ * vec) - 0.1f;
		jump = 0.0;
		if (vec >= 1) jumpFlag = true;
	}
	else
	{
		int mvnaet = 0;
	}
}
