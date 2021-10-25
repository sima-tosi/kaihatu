#pragma once
#include "AcEnemy.h"

enum class DOSUN
{
	STANDBY,
	FALL,
	FtoB,
	BACK,
	BtoS
};

class AcDosunn :
    public AcEnemy
{
public:
	AcDosunn(AcCamera* camera, AcMap* map, Vector2F pos);

	void Init(void) override;
	void UpData(double delta, Vector2F pPos)override;
	void MapHit(void)override;
private:
	DOSUN dosun;
	Vector2F startPos;
	double stayTime;
};

