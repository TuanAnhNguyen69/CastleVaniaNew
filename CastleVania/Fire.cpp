#include "Fire.h"
#include "Simon.h"


Fire::Fire() : Enemy()
{
	active = true;
}

Fire::Fire(float _x, float _y, float _direction) :
	Enemy(_x, _y, 0, 0, EnumID::Fire_ID)
{
	hp = 1;
	damage = 2;
	lifeTime = 0;
	active = true;
	canBeKilled = true;
	type = ObjectType::Enemy_Type;
	if (_direction > 0)
		vX = SPEED_FIRE;
	else
		vX = -SPEED_FIRE;
}



Fire::~Fire()
{
}

void Fire::Update(int dt)
{
	lifeTime += dt;
	x += vX * dt;
	if (lifeTime >= 3000) 
		active = false;
}

void Fire::Draw(GCamera *camera)
{
	if (sprite == NULL || !active)
		return;
	if (x <= camera->viewport.x || x >= camera->viewport.x + G_ScreenWidth)
	{
		active = false;
		return;
	}
	D3DXVECTOR2 pos = camera->Transform(x, y);
	if (vX > 0)
		sprite->DrawFlipX(pos.x, pos.y);
	else
		sprite->Draw(pos.x, pos.y);
}

void Fire::CollSimon(GameObject* simon, int dt)
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
			{
				simon->ReceiveDamage(this->damage);
				dynamic_cast<Simon*>(simon)->KnockBack();
			}	
		}
	}
}