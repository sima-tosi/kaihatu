#include "AcKuribo.h"
#include "AcCamera.h"


AcKuribo::AcKuribo(AcCamera* camera)
{
	mCamera = camera;
	Init();
}

void AcKuribo::Init(void)
{
	pos = { 1400,600 };
	vec = { -5,0 };
	size = { 32,32 };
	jump = 0;
}

bool AcKuribo::PlayerDeath(Vector2F pPos, Vector2 pSize)
{
	if (pos.x_ + size.x_ > pPos.x_ - pSize.x_ &&
		pos.x_ - size.x_ < pPos.x_ + pSize.x_ &&
		pos.y_ + size.y_ > pPos.y_ - pSize.y_ &&
		pos.y_ - size.y_ < pPos.y_ + pSize.y_)
	{
		if (pos.y_ > pPos.y_ + pSize.y_)
		{
			kill = true;
		}
		else
		{
			return true;
		}
	}
	return false;
}
