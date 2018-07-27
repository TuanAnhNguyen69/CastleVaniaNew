#include "Knife.h"



Knife::Knife() : Weapon()
{
	active = true;
}

Knife::Knife(float _posX, float _posY, int _width, int _height, float _direction)
	:Weapon(_posX, _posY, _width, _height, _direction, EnumID::Knife_ID)
{
	active = true;
}

Knife::~Knife()
{
}

