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
	AcDosunn(AcCamera* camera);

	void Init(void) override;
	void UpData(double delta, Vector2F pPos)override;
private:
	DOSUN dosun;
	Vector2F startPos;
	double stayTime;
};

