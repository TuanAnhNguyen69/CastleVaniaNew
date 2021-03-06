#include "Boomerang.h"



Boomerang::Boomerang() : Weapon()
{
	active = true;
}

Boomerang::Boomerang(float _posX, float _posY, int _width, int _height, float _direction)
	: Weapon(_posX, _posY, _width, _height, _direction, EnumID::Boomerang_ID)
{
	active = true;
}

Boomerang::~Boomerang()
{
}

void Boomerang::Update(int deltaTime)
{
	int range = 0;
	int lifeTime = 0;

	if (lifeTime > 0 && lifeTime <= BOOMERANG_LIFE_TIME)
	{
		lifeTime += deltaTime;
	}
	else
	{
		range += vX * deltaTime;
		posX += vX * deltaTime;
		if (abs(range) > BOOMERANG_RAGE && lifeTime == 0)
		{
			lifeTime += deltaTime;
			vX = -vX;
		}
	}
	sprite->Update(deltaTime);
}

void Boomerang::Collision()
{
	//Chua dinh nghia
}