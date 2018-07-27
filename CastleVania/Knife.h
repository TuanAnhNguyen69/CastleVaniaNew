#pragma once
#include "Weapon.h"
class Knife :
	public Weapon
{
public:
	Knife();
	Knife(float _posX, float _posY, int _width, int _height, float _direction);
	~Knife();
};

