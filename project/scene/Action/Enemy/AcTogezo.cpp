#include "AcTogezo.h"

AcTogezo::AcTogezo(AcCamera* camera, AcMap* map, Vector2F pos)
{
	mCamera = camera;
	mMap = map;
	AcTogezo::pos = pos;
	Init();
}

void AcTogezo::Init(void)
{
	vec = { -5,0 };
	size = { 32,32 };
	jump = 0;
}
