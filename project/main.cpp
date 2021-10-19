#include <DxLib.h>
#include "Screen.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	Screen::GetInstance().Run();
	return true;
}