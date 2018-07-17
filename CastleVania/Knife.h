#pragma once
#include "Weapon.h"
class Knife :
	public Weapon
{
public:
	Knife();
	Knife(float _posX, float _posY, float _direction);
	~Knife();
};

