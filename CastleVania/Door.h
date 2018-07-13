#pragma once
#include "GameObject.h"
class Door :
	public GameObject
{
public:
	Door();
	Door(float _posX, float _posY, int _width, int _height, EnumID _id);
	~Door();
};

