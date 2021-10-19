#pragma once
#include "../../input/Control.h"
#include "../../Vector2.h"

class AcCamera;
class AcEnemy;
class AcPlayer
{
public:
	AcPlayer(AcCamera* camera);

	void Init(void);
	void UpData(KeyDate keyData, double delta);
	bool EnemyHit(AcEnemy* enemy);
	void Draw(void);

	Vector2F GetPos(void) { return pos; };
private:
	Vector2F pos;
	Vector2 size;
	float jump;
	bool kill;

	AcCamera* mCamera;
};

