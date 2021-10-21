#pragma once
#include "../../Vector2.h"
#include "../map/TMXobj.h"
#include <map>

class Action;
class AcMap
{
public:
	AcMap(Action* action);
	~AcMap();
	void Init(void);
	void Draw(float cameraPos);
	bool HitMap(Vector2F pos, int jumpVec);
	Vector2 BackPos(Vector2F pos, int vec);
private:
	Vector2 chipSize;
	Vector2 mapSize;

	int mapScreen;
	TMXobj* tmx;

	void ScreenDraw(void);

	bool OneMoveBlock(int vec);
	void BreakBlock(Vector2F pos, int vec);
	void LimitBlock(Vector2F pos, int vec);
	void ItemBlock(Vector2F pos, int vec);

	std::map<int, int> limitBlock;

	Action* mAction;
};

