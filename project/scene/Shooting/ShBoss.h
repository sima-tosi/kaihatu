#pragma once
#include "../../Vector2.h"

enum class BossMove
{
	Entry,
	Stay,
	EsCape,
};

class ShPlayer;
class Shooting;
class ShBoss
{
public:
	double SHOT_TIME = 0.5;
	int MAX_LIFE = 100;

	ShBoss(Shooting* _shooting, ShPlayer* _player);
	~ShBoss();

	void Init(void);
	void UpDate( double delta);
	void Draw(void);

	bool PlayerHit(Vector2F pPos, Vector2F pSize);
	bool ShotHit(Vector2F sPos, Vector2F sSize);
	bool finish(void) { return escape || life <= 0; };
private:

	void Shot1(Vector2F sPos);
	void Shot2(Vector2F sPos);
	void Shot3(Vector2F sPos);

	Shooting* shooting;
	ShPlayer* player;

	Vector2F pos;
	Vector2F size;
	Vector2F hitSize;
	Vector2F shotPos1;
	Vector2F shotPos2;

	double shot1Time;
	double shot2Time;
	double shot3Time;

	BossMove bossMove;

	int life;
	bool escape = false;
	double escapeTime;
};

