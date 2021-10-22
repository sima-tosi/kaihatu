#pragma once
#include "AcEnemy.h"

class AcCamera;

class AcKuribo :
    public AcEnemy
{
public:
	AcKuribo(AcCamera* camera, AcMap* map);

	void Init(void) override;
	UniPlay PlayerDeath(UniPlay player) override;
private:
};

