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

	Vector2F GetPos(void) { return pos; };
	Vector2 GetSize(void) { return size; };
protected:
	Vector2F pos;
	Vector2F vec;
	Vector2 size;
	float jump;

	AcCamera* mCamera;
};

