#pragma once
#include "GameObject.h"
#include "EnumManager.h"

class Stair :
	public GameObject
{
public:
	Stair();
	Stair(float _posX, float _posY, int _width, int _height, EnumID _id);
	~Stair();
};

