#include "MovingPlatform.h"



MovingPlatform::MovingPlatform() : ActiveObject()
{
}

MovingPlatform::MovingPlatform(float x, float y) : ActiveObject(x, y, 0.1f, 0, EnumID::MovingPlatform_ID)
{
	active = true;
	sprite = new GSprite(TextureManager::getInstance()->getTexture(EnumID::MovingPlatform_ID), 0, 0, 1000);
	vX = 0.1f;
}


MovingPlatform::~MovingPlatform()
{
}

void MovingPlatform::Draw(GCamera* camera)
{
	if (sprite != NULL)
	{
		D3DXVECTOR2 pos = camera->Transform(x, y);
		sprite->Draw(pos.x, pos.y);
	}
}

void MovingPlatform::Update(int dt)
{
	if (!active)
		return;
	x += vX * dt;
	sprite->Update(dt);
}

void MovingPlatform::Collision(list<GameObject*>& obj, int dt)
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
						this->vX = -this->vX;
						return;
					}
				}
			}
		}
	}
}
