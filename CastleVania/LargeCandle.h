#pragma once
#include "GameObject.h"
#include "EnumManager.h"

class LargeCandle :
	public GameObject
{
public:
	LargeCandle();
	LargeCandle(float _posX, float _posY);
	~LargeCandle();
};

