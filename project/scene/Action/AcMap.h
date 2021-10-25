#pragma once
#include "../../Vector2.h"
#include "map/TMXobj.h"
#include <map>

class Action;
class AcMap
{
public:
	AcMap(Action* action);
	~AcMap();
	void Init(void);
	void Draw(float cameraPos);
	void UpData(void);
	bool HitMap(Vector2F pos, int jumpVec);
	Vector2 BackPos(Vector2F pos, int vec);

	Vector2 GetMapSize(void) { return mapSize; };
	Vector2 GetChipSize(void) { return chipSize; };
	int GetMapData(std::string name,int x, int y);
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

