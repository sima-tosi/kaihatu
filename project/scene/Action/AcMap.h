#pragma once
#include "../../Vector2.h"
#include <vector>

class AcMap
{
public:
	AcMap();
	void Init(void);
	void Draw(Vector2F cameraPos);
	bool HitMap(Vector2 pos, float jumpVec);

private:
	Vector2 chipSize;
	Vector2 mapSize;
	std::vector<int> map;

	int mapScreen;
	std::vector<int> mapImage;

	void ScreenDraw(void);
};

