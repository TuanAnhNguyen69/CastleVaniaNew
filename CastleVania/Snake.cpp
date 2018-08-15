#include "Snake.h"
#include "Simon.h"



Snake::Snake() : Enemy()
{
	active = true;
}

Snake::Snake(float _x, float _y, float _direction)
	: Enemy(_x, _y, 0, 0, EnumID::Snake_ID)
{
	hp = 1;
	damage = 1;

	lifeTime = 0;
	active = true;
	canBeKilled = true;
	damage = 4;
	type = ObjectType::Enemy_Type;
	if (_direction > 0)
		vX = SNAKE_SPEED;
	else
		vX = -SNAKE_SPEED;

	vY = -0.3;
	sprite = new GSprite(TextureManager::getInstance()->getTexture(id),0, 1, 100);
	isGround = false;
}


Snake::~Snake()
{
}

void Snake::Draw(GCamera* camera)
{
	if(sprite == NULL || !active)
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

void Snake::Update(int dt)
{
	lifeTime += dt;
	x += vX * dt;
	if (lifeTime >= 900)
		active = false;
	if (isGround)
		vY = 0;
	y += vY * dt;
}


void Snake::Collision(list<GameObject*> &obj, int dt)
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
						this->y = other->y + this->height;
						return;
					}
				}
			}
		}
	}
}

void Snake::CollSimon(GameObject* simon, int dt)
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
