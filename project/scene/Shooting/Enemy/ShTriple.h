#pragma once
#include "ShEnemy.h"
class ShTriple :
    public ShEnemy
{
public:
	ShTriple(Shooting* _shooting,Vector2F _pos, int _image);
	~ShTriple();
	void UpData(double delta) override;

private:
};

