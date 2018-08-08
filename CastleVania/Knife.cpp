#include "Knife.h"



Knife::Knife() : Weapon()
{
	active = true;
}

Knife::Knife(float _posX, float _posY, float _direction)
	:Weapon(_posX, _posY, _direction, EnumID::Knife_Weapon_ID)
{
	active = true;
	if (_direction < 0.0)
		vX = -KNIFE_SPEED;
	else
		vX = KNIFE_SPEED;
}

Knife::~Knife()
{
}

