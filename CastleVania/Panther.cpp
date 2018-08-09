#include "Panther.h"



Panther::Panther() : Enemy()
{
	active = true;
}

Panther::Panther(float _x, float _y)
	: Enemy(_x, _y, PANTHER_SPEED, 0, EnumID::Panther_ID)
{
	hp = 1;
	damage = 2;
	point = 200;
	active = true;
	canBeKilled = true;
	type = ObjectType::Enemy_Type;
	hasJump = false;
	isJump = false;
	isGrounding = false;
}
Panther::~Panther()
{
}

void Panther::Draw(GCamera* camera)
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

void Panther::Update(int dt)
{
	x += vX * dt;
	if (x <= width / 2 + 5 || x >= G_MapWidth - width / 2 - 5)
		vX = -vX;
	
	if(isJump)
	{
		y += vY;
		if (y >= PANTHER_JUMP_HEIGHT)
			vY = -vY;

		//Neu cham dat, chua dinh nghia
		if (false)
		{
			isJump = false;
			isGrounding = true;
			vY = 0.0f;
		}
	}
	else
		sprite->Update(dt);

	if (hasJump && isGrounding)
	{
		vX = -vX;
		x += vX * dt;
		sprite->Update(dt);
	}
}

void Panther::SetActive(float _posX_Simon, float _posY_Siomon)
{
	bool simonLeft = true;
	if (x < _posX_Simon)
		simonLeft = false;

	if (abs(x - _posX_Simon) <= 200)
	{
		if ((y - _posY_Siomon) <= 0 && (y - _posY_Siomon) >= -50)
		{
			if (!simonLeft)
				vX = PANTHER_SPEED;
			else
				vX = -PANTHER_SPEED;
		}
		else
			if ((y - _posY_Siomon) >= 30 && (y - _posY_Siomon) <= 150)
				Jump();
	}
}

void Panther::Jump()
{
	isGrounding = false;
	vX = -PANTHER_SPEED;
	vY = PANTHET_JUMP_SPEED;
	isJump = true;
	sprite = new GSprite(TextureManager::getInstance()->getTexture(EnumID::Panther_ID), 1, 3, 60);
	sprite->SelectIndex(3);
	
}

void Panther::Collision(list<GameObject*> &obj, int dt)
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
					this->y = other->y + this->height;
					isGrounding = true;
				}
			}
		}
	}
}