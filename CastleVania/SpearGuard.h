#pragma once
#include "ActiveObject.h"

#define SPEARGUARD_SPEED 0.8f

class SpearGuard :
	public ActiveObject
{
public:
	SpearGuard();
	SpearGuard(float _posX, float _posY, int _width, int _height);
	~SpearGuard();
};

