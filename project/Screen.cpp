#include <DxLib.h>
#include "Screen.h"
#include "scene/Game.h"
#include "input/Keyboard.h"

Screen::Screen()
{
	Init();
}
Screen::~Screen()
{
}

bool Screen::Init(void)
{
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 32);
	ChangeWindowMode(true);
	SetWindowText("1916016_ìáë∫èrãP");

	if (DxLib_Init() == -1) return false;

	SetDrawScreen(DX_SCREEN_BACK);

	scene = std::make_unique<Game>();

	return true;
}

bool Screen::Run(void)
{
	control = std::make_unique<Keyboard>();
	control->SetUp(0);

	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		(*control)();
		ClsDrawScreen();

		scene = scene->UpDate(std::move(scene),
							  control->GetCntData());
		scene->Draw();

		ScreenFlip();
	}

	DxLib::DxLib_End();
	return true;
}

