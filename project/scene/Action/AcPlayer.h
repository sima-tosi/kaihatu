#pragma once
#include "../../input/Control.h"
#include "../../Vector2.h"

class AcCamera;
class AcEnemy;
class AcMap;
class AcPlayer
{
public:
	AcPlayer(AcCamera* camera, AcMap* map);

	void Init(void);
	void UpData(KeyDate keyData, double delta);
	void Draw(void);

	Vector2F GetPos(void) { return pos; };
	Vector2 GetSize(void) { return size; };
	void Death(void);
	bool GetKill(void) { return kill; };
	void Item(void) { item = true; }
private:
	void MapHitLR(int vec);
	void MapHitUD(int vec);

	Vector2F pos;
	Vector2 size;
	double muteki;
	float jump;
	bool item;
	bool kill;
	bool jumpFlag;

	AcCamera* mCamera;
	AcMap* mMap;
};

