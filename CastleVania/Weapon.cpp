#include "Weapon.h"

#define SPEED_WEAPON 0.5f


Weapon::Weapon() : ActiveObject()
{
}

Weapon::Weapon(float _posX, float _posY, float _direction, EnumID id) :
	ActiveObject(_posX, _posY, 0, 0, id)
{
	active = true;
	if (_direction > 0)
		vX = SPEED_WEAPON;
	else
		vX = -SPEED_WEAPON;
}


Weapon::~Weapon()
{
}

void Weapon::Draw(GCamera* camera)
{
	ActiveObject::Draw(camera);
}

void Weapon::Update(int deltaTime)
{
	if (sprite == NULL || !active)
		return;
	x += vX * deltaTime;
	y += vY * deltaTime;
	sprite->Update(deltaTime);
}

void Weapon::Collision()
{
	//Chua dinh nghia
}