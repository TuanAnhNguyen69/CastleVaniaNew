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

void Boomerang::CollSimon(GameObject* simon, int dt)
{
	Box box = this->GetBox();
	Box boxSimon = simon->GetBox();
	Box broadphasebox = getSweptBroadphaseBox(box, dt);
	if (AABBCheck(broadphasebox, boxSimon))
	{
		ECollisionDirection colDirection;
		float collisionTime = sweptAABB(box, boxSimon, colDirection, dt);
		if (collisionTime < 1.0f && collisionTime > 0.0)
		{
			if (simon->id == EnumID::Simon_ID)
				this->active = false;
		}
	}
}
