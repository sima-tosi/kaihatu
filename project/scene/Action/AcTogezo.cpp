#include "AcTogezo.h"

AcTogezo::AcTogezo(AcCamera* camera, AcMap* map)
{
	mCamera = camera;
	mMap = map;
	Init();
}

void AcTogezo::Init(void)
{
	pos = { 1400,600 };
	vec = { -5,0 };
	size = { 32,32 };
	jump = 0;
}
