#pragma once
#include "ShEnemy.h"
class ShTriple :
    public ShEnemy
{
public:
	ShTriple(Shooting* _shooting,Vector2F _pos);
	~ShTriple();
	void UpData(double delta) override;

private:
};

