#include "MedusaBoss.h"





MedusaBoss::MedusaBoss() : Enemy()
{
}

MedusaBoss::MedusaBoss(float _x, float _y) :  Enemy(_x, _y, MEDUSA_SPEED, 0, EnumID::Medusa_ID)
{
	damage = 2;
	hp = 20;
	point = 1000;
	active = true;
	canBeKilled = true;
	type = ObjectType::Enemy_Type;
	getUp = false;
	spriteSleep = new GSprite(TextureManager::getInstance()->getTexture(EnumID::Medusa_ID), 4, 4, 100);
	spriteAttack = new GSprite(TextureManager::getInstance()->getTexture(EnumID::Medusa_ID), 0, 3, 100);

	//sprite = spriteSleep;
	x0 = _x;
	isLeft = false;
	lifeTime = 0;
	listSnake = new list<ActiveObject*>();
	reloadTime = 0;
}

MedusaBoss::~MedusaBoss()
{
	delete listSnake;
}

void MedusaBoss::UpdateSnake(float dt)
{
	list<ActiveObject*>::iterator obj = listSnake->begin();
	while (obj != listSnake->end())
	{
		if (!(*obj)->active)
			listSnake->erase(obj++);
		else
		{
			(*obj)->Update(dt);
			++obj;
		}
	}
}

void MedusaBoss::DrawSnake(GCamera * camera)
{
	for (list<ActiveObject*>::iterator snake = listSnake->begin(); snake != listSnake->end(); snake++)
	{
		(*snake)->Draw(camera);
	}
}

void MedusaBoss::MovePath(int dt)
{
	x += vX * dt * 2;
	y = std::sin(x * 0.02) * 2 + y + 0.0000001;
}

void MedusaBoss::Draw(GCamera * camera)
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
	this->DrawSnake(camera);
}

void MedusaBoss::Update(int dt)
{
	
	
}

void MedusaBoss::Update(float _xSimon, float _ySimon, int dt)
{
	/*
	lifeTime += dt;
	if (lifeTime > 500)
	{
		this->isDeath = true;
		this->active = false;
	}
	*/
	Dying(dt);

	if (active)
	{
		if (getUp)
		{
			sprite = spriteAttack;
			this->MovePath(dt);
			sprite->Update(dt);

			if (x > _xSimon)
			{
				isLeft = false;
			}
			else
			{
				isLeft = true;
			}
			
			if (abs(x - x0) > 180)
				vX = -vX;
			
			if (_ySimon > y)
				vY = 0.2;
			else
				vY = 0;

			reloadTime += dt;
			if (reloadTime % 60 == 0)
			{
				if (isLeft)
					listSnake->push_back(new Snake(x, y - 30, 1));
				else
					listSnake->push_back(new Snake(x, y - 30, -1));
			}

			UpdateSnake(dt);
		}
		else
			sprite = spriteSleep;
	}
	
}

void MedusaBoss::Collision(list<GameObject*> &obj, int dt)
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
						this->vX = - this->vX;
						//this->active = false;
					}
					if (colDirection == ECollisionDirection::Colls_Bot)
					{
						this->y = other->y + this->height;
						vY = 1;
						return;
					}
				}
			}
		}
	}

	for (list<ActiveObject*>::iterator snake = listSnake->begin(); snake != listSnake->end(); snake++)
	{
		(*snake)->Collision(obj, dt);
	}	
}

void MedusaBoss::CollSimon(GameObject* simon, int dt)
{
	for (list<ActiveObject*>::iterator snake = listSnake->begin(); snake != listSnake->end(); snake++)
	{
		(*snake)->CollSimon(simon, dt);
	}
}

Box MedusaBoss::GetBox()
{
	Box box(x, y, width, height, vX, vY);
	return box;
}