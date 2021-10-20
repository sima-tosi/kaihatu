#pragma once
#include "../../Vector2.h"

enum class TYPE
{
	KURIBO,
	TOGEZO,
	DOSUNN
};

class AcCamera;
class AcEnemy
{
public:
	AcEnemy();

	virtual void Init(void) {};
	virtual void UpData(double delta,Vector2F pPos);
	virtual void Draw(void);
	virtual void MapHit(void);
	virtual bool PlayerDeath(Vector2F pPos, Vector2 pSize);

	Vector2F GetPos(void) { return pos; };
	Vector2 GetSize(void) { return size; };
	bool GetKill(void) { return kill; };

protected:
	Vector2F pos;
	Vector2F vec;
	Vector2 size;
	float jump;
	bool kill = false;
	bool turn = false;

	AcCamera* mCamera;
};

