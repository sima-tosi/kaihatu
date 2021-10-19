#pragma once
#include "AcEnemy.h"

class AcCamera;

class AcKuribo :
    public AcEnemy
{
public:
	AcKuribo(AcCamera* camera);

	void Init(void) override;

private:
};

