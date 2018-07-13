#pragma once
#include "GameObject.h"
#include "EnumManager.h"

class Barrier :
	public GameObject
{
public:
	Barrier();
	Barrier(float _posX, float _posY, int _width, int _height);
	~Barrier();
};

