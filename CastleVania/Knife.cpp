#include "Knife.h"



Knife::Knife() : Weapon()
{
	active = true;
}

Knife::Knife(float _posX, float _posY, float _direction)
	:Weapon(_posX, _posY, _direction, EnumID::Knife_ID)
{
	active = true;
}

Knife::~Knife()
{
}

