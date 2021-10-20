#pragma once
#include "AcEnemy.h"

class AcCamera;

class AcKuribo :
    public AcEnemy
{
public:
	AcKuribo(AcCamera* camera);

	void Init(void) override;
	bool PlayerDeath(Vector2F pPos, Vector2 pSize) override;
private:
};

