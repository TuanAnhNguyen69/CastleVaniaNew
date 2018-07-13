#pragma once
#include "GameObject.h"
#include "EnumManager.h"

class Brick :
	public GameObject
{
public:
	Brick();
	Brick(float _posX, float _posY, int _width, int _height);
	~Brick();
};

