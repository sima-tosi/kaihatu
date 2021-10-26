#pragma once
#include "ShEnemy.h"

class ShPlayer;

class ShTackle :
    public ShEnemy
{
public:
	ShTackle(ShPlayer* _player, Vector2F _pos);
	~ShTackle();
	void UpData(double delta) override;

private:
	ShPlayer* player;
};

