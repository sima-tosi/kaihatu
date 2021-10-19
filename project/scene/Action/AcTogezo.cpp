#include "AcTogezo.h"

AcTogezo::AcTogezo(AcCamera* camera)
{
	mCamera = camera;
	Init();
}

void AcTogezo::Init(void)
{
	pos = { 1400,600 };
	vec = { -5,0 };
	size = { 32,32 };
	jump = 0;
}
