#pragma once
#include "ActiveObject.h"

#define SPEARGUARD_SPEED 0.8f
#define SPEARGUARD_RANGE 100

class SpearGuard :
	public ActiveObject
{
public:

	int posX0;


	void Update(int deltaTime);

	SpearGuard();
	SpearGuard(float _posX, float _posY);
	~SpearGuard();
};

