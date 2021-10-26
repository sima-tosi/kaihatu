#include "ShShot.h"
#include <DxLib.h>

ShShot::ShShot(Vector2F _pos, Vector2F _vec)
{
	pos = _pos;
	vec = _vec;
	size = { 4,4 };
}

ShShot::~ShShot()
{
}

void ShShot::UpData(double delta)
{
	pos += vec;

	if (pos.x_ > 1024 + size.x_ || pos.x_ < 0 - size.x_ ||
		pos.y_ > 768  + size.y_ || pos.y_ < 0 - size.x_) kill = true;
}

void ShShot::Draw(void)
{
	DrawBox(pos.x_ - size.x_, pos.y_ - size.y_,
		pos.x_ + size.x_, pos.y_ + size.y_,
		0xffff00, true);
}
