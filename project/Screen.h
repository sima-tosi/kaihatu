#pragma once
#include<memory>

#define SCREEN_SIZE_X 1024
#define SCREEN_SIZE_Y 768
class Control;
class Scene;
class Screen
{
public:
	static Screen& GetInstance()
	{
		static Screen s_Instance;
		return s_Instance;
	}

	bool Run(void);

private:
	Screen();
	~Screen();

	bool Init(void);

	std::unique_ptr <Scene>   scene;
	std::unique_ptr <Control> control;
};

