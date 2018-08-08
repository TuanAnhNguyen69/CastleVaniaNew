#pragma once
#include "Weapon.h"

#define KNIFE_SPEED 1.0f

class Knife :
	public Weapon
{
public:
	Knife();
	Knife(float _posX, float _posY, float _direction);
	~Knife();
};

