#pragma once
#include "../../Vector2.h"

class ShShot
{
public:
	ShShot(Vector2F _pos,Vector2F _vec);
	~ShShot();

	void UpData(double delta);
	void Draw(void);

	void KillSet(void) { kill = true; }
	bool GetKill(void) { return kill; }

	Vector2F GetPos(void) { return pos; };
	Vector2F GetSize(void) { return size; };
public:
	Vector2F pos;
	Vector2F size;
	Vector2F vec;

	bool kill = false;
};

