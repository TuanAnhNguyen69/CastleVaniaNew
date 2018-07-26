#pragma once
#include "GameObject.h"
#include "EnumManager.h"

class Brick :
	public GameObject
{
public:
	bool isBreakable;
	Brick();
	Brick(float _posX, float _posY, int _width, int _height, bool breakable);
	~Brick();
};

