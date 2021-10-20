#include "AcEnemy.h"
#include "AcCamera.h"
#include <DxLib.h>

AcEnemy::AcEnemy()
{
}

void AcEnemy::UpData(double delta, Vector2F pPos)
{
	float cameraPos = mCamera->GetPos();

	if (cameraPos + 1280 > pos.x_ - size.x_)
	{
		pos.x_ += vec.x_;
	}
	jump -= 0.3;
	pos.y_ -= jump;
	if (pos.y_ > 720 - size.y_)
	{
		pos.y_ = 720 - size.y_;
		jump = 0.0f;
	}
}

void AcEnemy::Draw(void)
{
	float cameraPos = mCamera->GetPos();
	DrawBox(pos.x_ - cameraPos - size.x_, pos.y_ - size.y_,
		pos.x_ - cameraPos + size.x_, pos.y_ + size.y_,
		0x994C00, true);
}

void AcEnemy::MapHit(void)
{
	// mapŠO‚Éo‚é‚Æ
	{
		kill = true;
		return;
	}

	// map‚É‚ ‚½‚é‚Æ
	{
		vec = -vec;
		turn = !turn;
	}
}

bool AcEnemy::PlayerDeath(Vector2F pPos, Vector2 pSize)
{
	if (pos.x_ + size.x_ > pPos.x_ - pSize.x_ &&
		pos.x_ - size.x_ < pPos.x_ + pSize.x_ &&
		pos.y_ + size.y_ > pPos.y_ - pSize.y_ &&
		pos.y_ - size.y_ < pPos.y_ + pSize.y_)
	{
		return true;
	}
	return false;
}
