#include "Zombie.h"



Zombie::Zombie() : ActiveObject()
{
	active = true;
}

Zombie::Zombie(float _posX, float _posY)
	:ActiveObject(_posX, _posY, ZOMBIE_SPEED, 0, EnumID::Zombie_ID)
{
	active = true;
	canBeKilled = true;
	type = ObjectType::Enemy_Type;
}


Zombie::~Zombie()
{
}

void Zombie::Draw(GCamera* camera)
{
	ActiveObject::Draw(camera);
}

void Zombie::Update(int deltaTime)
{
	if (posX * deltaTime > ZOMBIE_RANGE)
		vX = -vX;
	sprite->Update(deltaTime);
}

void Zombie::Collision()
{

}