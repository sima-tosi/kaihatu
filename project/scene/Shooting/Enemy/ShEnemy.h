#pragma once
#include "../../../Vector2.h"

class Shot;
class ShEnemy
{
public:
	ShEnemy() {};
	virtual void UpData(double delta);
	virtual void Draw(void);
	virtual bool PlayerHit(Vector2F pPos, Vector2F pSize);
	virtual void ShotHit(Vector2F sPos, Vector2F sSize);

	bool Kill(void) { return kill; };
private:
	virtual void makeShot(void) {};

	Vector2F pos;
	Vector2F size;
	Vector2F vec;
	double time;
	bool kill = false;

	Shot* shot;
};

