#pragma once
#include "../../Vector2.h"
#include "../../input/Control.h"

enum class ShotMode
{
	Non,
	Triple,
	Side,
	Quick
};

class Shooting;
class ShPlayer
{
public:
	double SHOT_TIME = 0.5;
	float SPEED = 7.0f;

	ShPlayer(Shooting* _shooting);
	~ShPlayer();

	void Init(void);
	void UpDate(KeyDate keyData, double delta);
	void Draw(void);

	void Kill(void);
	bool ShotHit(Vector2F sPos, Vector2F sSize);
	void GetItem(ShotMode Item);
	Vector2F GetPos(void) { return pos; };
	Vector2F GetHitSize(void) { return hitSize; };
private:
	Shooting* shooting;

	Vector2F pos;
	Vector2F size;
	Vector2F hitSize;
	ShotMode mode;

	double shotTime;
	void NonMake(void);
	void TripleMake(void);
	void SideMake(void);
	void QuickMake(void);

	bool kill;
	double killTime;
};

