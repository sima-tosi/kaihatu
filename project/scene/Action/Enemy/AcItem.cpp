#include "AcItem.h"
#include "../AcPlayer.h"

AcItem::AcItem(AcCamera* camera, AcMap* map, Vector2F pos, int _image)
{
	mCamera = camera;
	mMap = map;
	AcItem::pos = pos;
	image = _image;
	Init();
}

void AcItem::Init(void)
{
	vec = { -5,0 };
	size = { 32,32 };
	jump = 0;
}

UniPlay AcItem::PlayerDeath(UniPlay player)
{
	Vector2F pPos = player->GetPos();
	Vector2 pSize = player->GetSize();

	if (pos.x_ + size.x_ > pPos.x_ - pSize.x_ &&
		pos.x_ - size.x_ < pPos.x_ + pSize.x_ &&
		pos.y_ + size.y_ > pPos.y_ - pSize.y_ &&
		pos.y_ - size.y_ < pPos.y_ + pSize.y_)
	{
		player->Item();
		kill = true;
	}

	return std::move(player);
}
