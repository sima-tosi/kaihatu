#include "AcKuribo.h"
#include "AcCamera.h"
#include "AcPlayer.h"

AcKuribo::AcKuribo(AcCamera* camera, AcMap* map)
{
	mCamera = camera;
	mMap = map;
	Init();
}

void AcKuribo::Init(void)
{
	pos = { 1400,600 };
	vec = { -5,0 };
	size = { 32,32 };
	jump = 0;
}

UniPlay AcKuribo::PlayerDeath(UniPlay player)
{
	Vector2F pPos = player->GetPos();
	Vector2 pSize = player->GetSize();

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
			player->Death();
		}
	}
	return std::move(player);
}
