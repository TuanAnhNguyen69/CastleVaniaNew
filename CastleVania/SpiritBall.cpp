#include "SpiritBall.h"



SpiritBall::SpiritBall(): ActiveObject()
{
	active = false;
}

SpiritBall::SpiritBall(float _x, float _y) : ActiveObject(_x, _y, 0, -0.5f, EnumID::SpiritBall_ID)
{
	active = false;
	sprite = new GSprite(TextureManager::getInstance()->getTexture(EnumID::SpiritBall_ID), 80);
	isGround = false;
}



SpiritBall::~SpiritBall()
{
}

void SpiritBall::Draw(GCamera * camera)
{
	if (sprite == NULL || !active)
		return;
	D3DXVECTOR2 pos = camera->Transform(x, y);
	sprite->Draw(pos.x, pos.y);
}

void SpiritBall::Update(int dt)
{
	if (sprite == NULL)
		return;
	if (isGround)
		vY = 0;
	else
		y -= vY + dt;
	sprite->Update(dt);
}

void SpiritBall::Collision(list<GameObject*> &obj, int dt)
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
					if (colDirection == ECollisionDirection::Colls_Bot)
					{
						isGround = true;
						vY = 0;
						this->y = other->y + this->height;
						return;
					}
				}
			}
		}
	}
}


