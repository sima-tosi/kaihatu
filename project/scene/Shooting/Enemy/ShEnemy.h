#pragma once
#include "../../../Vector2.h"

class Shooting;
class ShEnemy
{
public:
	ShEnemy() {};
	virtual void UpData(double delta);
	virtual void Draw(void);
	virtual bool PlayerHit(Vector2F pPos, Vector2F pSize);
	virtual bool ShotHit(Vector2F sPos, Vector2F sSize);

	bool GetKill(void) { return kill; };

protected:
	virtual void makeShot(void) {};

	Vector2F pos;
	Vector2F size = { 32,32 };
	Vector2F vec;
	double shotTime;
	bool kill = false;

	Shooting* scene;
};

