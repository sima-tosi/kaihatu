#include "AcEnemy.h"
#include "../AcCamera.h"
#include "../AcPlayer.h"
#include "../AcMap.h"
#include <DxLib.h>

AcEnemy::AcEnemy()
{
}

void AcEnemy::UpData(double delta, Vector2F pPos)
{
	float cameraPos = mCamera->GetPos();
	if (!move) move = cameraPos + 1280 > pos.x_ - size.x_;

	if (move)
	{
		pos.x_ -= vec.x_;
		int moveVec = vec.x_ > 0 ? -1 : 1;

		if(MapHitLR(moveVec)) AcEnemy::vec.x_ *= -1;

		jump -= 0.3;
		pos.y_ -= jump;
		moveVec = jump < 0 ? 1 : -1;

		MapHitUD(moveVec);
	}

	if (pos.y_ - size.y_ > 768)
	{
		kill = true;
	}
}

void AcEnemy::Draw(void)
{
	float cameraPos = mCamera->GetPos();
	DrawGraph(pos.x_ - cameraPos - size.x_, pos.y_ - size.y_,
		image, true);
}

void AcEnemy::MapHit(void)
{
	// map外に出ると
	{
		kill = true;
		return;
	}

	// mapにあたると
	{
		vec = -vec;
		turn = !turn;
	}
}

UniPlay AcEnemy::PlayerDeath(UniPlay player)
{
	Vector2F pPos = player->GetPos();
	Vector2 pSize = player->GetSize();

	if (pos.x_ + size.x_ > pPos.x_ - pSize.x_ &&
		pos.x_ - size.x_ < pPos.x_ + pSize.x_ &&
		pos.y_ + size.y_ > pPos.y_ - pSize.y_ &&
		pos.y_ - size.y_ < pPos.y_ + pSize.y_)
	{
		player->Death();
	}
	return std::move(player);
}

bool AcEnemy::MapHitLR(int vec)
{
	Vector2F cPos = { pos.x_ + (size.x_ * vec),pos.y_ };
	Vector2F tPos = cPos;
	tPos.y_ -= size.y_;
	Vector2F dPos = cPos;
	dPos.y_ += size.y_;

	if (mMap->HitMap(cPos, 0, false) || mMap->HitMap(tPos, 0, false) || mMap->HitMap(dPos, 0, false))
	{
		int cPosX = mMap->BackPos(cPos, vec).x_;
		pos.x_ = cPosX - (size.x_ * vec) - 0.1 * (vec);
		return true;
	}
	return false;
}

bool AcEnemy::MapHitUD(int vec)
{
	Vector2F cPos = { pos.x_,pos.y_ + (size.y_ * vec) };
	Vector2F lPos = cPos;
	lPos.x_ -= size.x_;
	Vector2F rPos = cPos;
	rPos.x_ += size.x_;

	bool stop = false;
	stop = mMap->HitMap(cPos, vec, false) || stop;
	stop = mMap->HitMap(lPos, vec, false) || stop;
	stop = mMap->HitMap(rPos, vec, false) || stop;

	if (stop)
	{
		int cPosY = mMap->BackPos(cPos, vec).y_;
		pos.y_ = cPosY - (size.y_ * vec) - 0.1f;
		jump = 0.0;
		return true;
	}

	return false;
}
