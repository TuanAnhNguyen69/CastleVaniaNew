#pragma once
#include "GameObject.h"
#include "EnumManager.h"

class Candle :
	public GameObject
{
public:
	Candle();
	Candle(float _posX, float _posY);
	~Candle();
};

