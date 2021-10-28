#pragma once
#include "ShEnemy.h"
class ShCurve :
    public ShEnemy
{
public:
	ShCurve(Shooting* _shooting, Vector2F _pos);
	~ShCurve();
	void UpData(double delta) override;

private:
	double downTime;
	float startPos;
};

