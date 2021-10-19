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
