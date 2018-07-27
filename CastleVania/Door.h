#pragma once
#include "GameObject.h"
class Door :
	public GameObject
{
public:
	bool isOpen;
	Door();
	Door(float _posX, float _posY, int _width, int _height);
	~Door();
};

