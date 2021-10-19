#pragma once
#include <memory>
#include "../input/Control.h"

class Scene
{
public:
	virtual std::unique_ptr<Scene> UpDate(std::unique_ptr<Scene> scene, KeyDate keyData) { return std::move(scene); };
	virtual void Draw(void) {};

private:


};

using UniScene = std::unique_ptr<Scene>;