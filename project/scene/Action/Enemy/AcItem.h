#pragma once
#include "AcEnemy.h"

class AcItem :
    public AcEnemy
{
public:

	AcItem(AcCamera* camera, AcMap* map,Vector2F pos);

	void Init(void) override;
	UniPlay PlayerDeath(UniPlay player) override;
private:
};

