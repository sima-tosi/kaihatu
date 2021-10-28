#pragma once
#include "../../Vector2.h"
#include <memory>

enum class TYPE
{
	KURIBO,
	TOGEZO,
	DOSUNN
};

class AcPlayer;
class AcCamera;
class AcMap;

using UniPlay = std::unique_ptr<AcPlayer>;

class AcEnemy
{
public:
	AcEnemy();

	virtual void Init(void) {};
	virtual void UpData(double delta, Vector2F pPos);
	virtual void Draw(void);
	virtual void MapHit(void);
	virtual UniPlay PlayerDeath(UniPlay player);

	Vector2F GetPos(void) { return pos; };
	Vector2 GetSize(void) { return size; };
	bool GetKill(void) { return kill; };

protected:
	bool MapHitLR(int vec);
	bool MapHitUD(int vec);

	Vector2F pos;
	Vector2F vec;
	Vector2 size;
	float jump;
	bool move = false;
	bool kill = false;
	bool turn = false;

	AcCamera* mCamera;
	AcMap* mMap;
};

