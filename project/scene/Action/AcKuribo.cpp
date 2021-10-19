#include "AcKuribo.h"
#include "AcCamera.h"


AcKuribo::AcKuribo(AcCamera* camera)
{
	mCamera = camera;
	Init();
}

void AcKuribo::Init(void)
{
	pos = { 1400,600 };
	vec = { -5,0 };
	size = { 32,32 };
	jump = 0;
}
