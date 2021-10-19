#pragma once
#include "../../Vector2.h"

class AcCamera
{
public:
	AcCamera(int mapSizeX, int screenSizeX);

	void Init(void);
	void UpData(float pPosX);

	float GetPos(void) { return mPosX; }
private:
	float mPosX;
	int mMapSizeX;
	int mScreenSizeX;
};

