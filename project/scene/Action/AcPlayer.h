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
	void Draw(void);

	Vector2F GetPos(void) { return pos; };
	Vector2 GetSize(void) { return size; };
	void Death(void) { kill = true; };
	bool GetKill(void) { return kill; };
private:
	void MapHitLR(int vec);
	void MapHitUD(int vec);

	Vector2F pos;
	Vector2 size;
	float jump;
	bool kill;

	AcCamera* mCamera;
};

