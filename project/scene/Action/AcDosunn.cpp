#include "AcDosunn.h"
#include <DxLib.h>

AcDosunn::AcDosunn(AcCamera* camera)
{
	mCamera = camera;
	Init();
}

void AcDosunn::Init(void)
{
	pos = { 1400,100 };
	vec = { 0, 10 };
	size = { 64,64 };
	jump = 0;

	dosun = DOSUN::STANDBY;
	startPos = pos;
}

void AcDosunn::UpData(double delta, Vector2F pPos)
{
	if (dosun == DOSUN::FALL)
	{
		pos.y_ += vec.y_;
		if (720 - size.y_ < pos.y_)
		{
			pos.y_ = 720 - size.y_;
			dosun = DOSUN::FtoB;
			stayTime = 1.0;
		}
	}
	else if (dosun == DOSUN::FtoB)
	{
		stayTime -= delta;
		if (stayTime <= 0.0)
		{
			dosun = DOSUN::BACK;
		}
	}
	else if (dosun == DOSUN::BACK)
	{
		pos.y_ -= vec.y_;
		if (startPos.y_ > pos.y_)
		{
			pos.y_ = startPos.y_;
			dosun = DOSUN::BtoS;
			stayTime = 1.0;
		}
	}
	else if (dosun == DOSUN::STANDBY)
	{
		Vector2F dir = pos - pPos;
		if (dir.x_ < 100.0f && dir.x_ > -100.0f)
		{
			dosun = DOSUN::FALL;
		}
	}
	else if (dosun == DOSUN::BtoS)
	{
		stayTime -= delta;
		if (stayTime <= 0.0)
		{
			dosun = DOSUN::STANDBY;
		}
	}
}

void AcDosunn::MapHit(void)
{
	// mapŠO‚Éo‚é‚Æ
	{
		kill = true;
		return;
	}

	if (dosun == DOSUN::FALL)
	{
		//map‚É“–‚½‚é‚Æ
		if (720 - size.y_ < pos.y_)
		{
			pos.y_ = 720 - size.y_;
			dosun = DOSUN::FtoB;
			stayTime = 1.0;
		}
	}
}
