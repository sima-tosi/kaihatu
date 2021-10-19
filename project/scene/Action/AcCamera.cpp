#include "AcCamera.h"
#include <DxLib.h>

AcCamera::AcCamera(int mapSizeX, int screenSizeX)
{
	mMapSizeX = mapSizeX;
	mScreenSizeX = screenSizeX;

	Init();
}

void AcCamera::Init(void)
{
	mPosX = 0.0f;
}

void AcCamera::UpData(float pPosX)
{
	float psPosX = pPosX - mPosX;
	
	if (psPosX > mScreenSizeX / 2)
	{
		float move = psPosX - mScreenSizeX / 2;
		mPosX = min(mPosX + move, mMapSizeX - mScreenSizeX);
	}
}
