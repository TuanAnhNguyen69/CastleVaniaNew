#include "Boomerang.h"



Boomerang::Boomerang() : Weapon()
{
	active = true;
	range = 0;

}

Boomerang::Boomerang(float _posX, float _posY, float _direction)
	: Weapon(_posX, _posY, _direction, EnumID::Boomerang_Weapon_ID)
{
	//active = true;
	range = 0;
	x0 = _posX;
	if (_direction < 0.0)
		isLeft = true;
	else
		isLeft = false;
}

Boomerang::~Boomerang()
{
}

void Boomerang::Update(int deltaTime)
{
	if (!active)
		return;
	else
	{
		x += vX * deltaTime;
		if (isLeft)
		{
			if ((x0 - x) > 200)
				vX = -vX;
		}
		else
			if ((x - x0) > 200)
				vX = -vX;
	}

	
	/*
	if (lifeTime != 0 && lifeTime <= BOOMERANG_LIFE_TIME)
	{
		lifeTime += deltaTime;
	}
	else
	{
		range += vX * deltaTime;
		x += vX * deltaTime;
		if (abs(range) > BOOMERANG_RAGE && lifeTime == 0)
		{
			lifeTime += deltaTime;
			vX = -vX;
		}
	}
	*/
	sprite->Update(deltaTime);
}

void Boomerang::Collision(list<GameObject*> &obj, int dt)
{
	list<GameObject*> listObject;
	list<GameObject*>::iterator it;
	for (it = obj.begin(); it != obj.end(); it++)
	{
		GameObject* other = (*it);

		Box box = this->GetBox();
		Box boxOther = other->GetBox();
		Box broadphasebox = getSweptBroadphaseBox(box, dt);
		if (other->id == EnumID::Simon_ID && AABBCheck(box, boxOther))
		{
			this->active = false;
		}
	}
}
