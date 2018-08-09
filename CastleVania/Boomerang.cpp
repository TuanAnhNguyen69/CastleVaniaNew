#include "Boomerang.h"



Boomerang::Boomerang() : Weapon()
{
	active = true;
	range = 0;

}

Boomerang::Boomerang(float _posX, float _posY, float _direction)
	: Weapon(_posX, _posY, _direction, EnumID::Boomerang_Weapon_ID)
{
	active = true;
	x0 = _posX;
	if (_direction < 0.0)
	{
		vX = -BOOMERANG_SPEED;
		isLeft = true;
	}
	else
	{
		vX = BOOMERANG_SPEED;
		isLeft = false;
	}
		
}

Boomerang::~Boomerang()
{
}

void Boomerang::Update(int dt)
{
	if (!active)
		return;
	else
	{
		x += vX * dt;
		if (isLeft)
		{
			if ((x0 - x) > 200)
				vX = -vX;
		}
		else
			if ((x - x0) > 200)
				vX = -vX;
		sprite->Update(dt);
	}

	
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
		if (AABBCheck(broadphasebox, boxOther))
		{
			ECollisionDirection colDirection;
			float collisionTime = sweptAABB(box, boxOther, colDirection, dt);
			if (collisionTime < 1.0f && collisionTime > 0.0)
			{
				switch (other->id)
				{
				case EnumID::Simon_ID:
					this->active = false;
					break;
				default:
					break;
				}
			}
		}
	}
}
