#pragma once
#include "AcEnemy.h"

class AcCamera;

class AcKuribo :
    public AcEnemy
{
public:
	AcKuribo(AcCamera* camera, AcMap* map, Vector2F pos, int _image);

	void Init(void) override;
	UniPlay PlayerDeath(UniPlay player) override;
private:
};

