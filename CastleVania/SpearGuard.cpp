#include "SpearGuard.h"



SpearGuard::SpearGuard() : Enemy()
{
}

SpearGuard::SpearGuard(float _x, float _y) 
	: Enemy(_x, _y, SPEARGUARD_SPEED, 0, EnumID::SpearGuard_ID)
{
	active = true;
	hp = 6;
	damage = 2;
	point = 400;
	canBeKilled = true;
	type = ObjectType::Enemy_Type;
	sprite = new GSprite(TextureManager::getInstance()->getTexture(EnumID::SpearGuard_ID), 0, 3, 80);
	x0 = _x;
	//this->vY = -0.4;
}
SpearGuard::~SpearGuard()
{
}

void SpearGuard::Update(int dt)
{
	if (!active)
		return;
	if (abs(x - x0) > 100)
		vX = -vX;
	x += vX * dt;
	//y += vY * dt;
	sprite->Update(dt);
}



void SpearGuard::Draw(GCamera* camera)
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

void SpearGuard::Collision(list<GameObject*> &obj, int dt)
{
	list<GameObject*>::iterator it;
	for (it = obj.begin(); it != obj.end(); it++)
	{
		GameObject* other = (*it);

		Box box = this->GetBox();
		Box boxOther = other->GetBox();
		Box broadphasebox = getSweptBroadphaseBox(box, dt);

		if (other->id == EnumID::Brick_ID)
		{
			if (AABBCheck(broadphasebox, boxOther))
			{
				ECollisionDirection colDirection;
				float collisionTime = sweptAABB(box, boxOther, colDirection, dt);
				if (collisionTime < 1.0f && collisionTime > 0.0)
				{
					if (colDirection == ECollisionDirection::Colls_Left ||
						colDirection == ECollisionDirection::Colls_Right)
					{
						this->vX = -vX;
					}
					/*
					if (colDirection == ECollisionDirection::Colls_Bot) {
						this->vY = 0;
						this->y = other->y + this->height + 1;
					}
					*/
				}
			}
		}
	}
}
