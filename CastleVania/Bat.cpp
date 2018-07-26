#include "Bat.h"



Bat::Bat() : ActiveObject()
{
	active = true;
}

Bat::Bat(float _posX, float _posY)
	: ActiveObject(_posX, _posY, BAT_SPEED, 0, EnumID::Bat_ID)
{
	active = true;
	canBeKilled = true;
	type = ObjectType::Enemy_Type;
	getUp = false;
	sprite = new GSprite(TextureManager::getInstance()->getTexture(EnumID::Bat_ID), 0, 3, 100);
}

Bat::~Bat()
{
}

void Bat::MovePath(int deltaTime)
{
	posX += vX * deltaTime;
	posY = sin(posX*3.14/180);
}

void Bat::Draw(GCamera* camera)
{
	ActiveObject::Draw(camera);
}

void Bat::Update(int deltaTime)
{
	if (getUp)
	{
		this->MovePath(deltaTime);
		sprite->Update(deltaTime);
	}

	if (hp <= 0)
	{
		Score += point;
		isDeath = true;
		return;
	}
}

void Bat::SetActive(float _posX_Simon, float _posY_Simon)
{
	if (abs(posX - _posX_Simon) <= 300 && abs(posY - _posY_Simon) <= 300)
	{
		getUp = true;
		if (posX - _posX_Simon > 0)
			vX = -BAT_SPEED;
		else
			vX = BAT_SPEED;
		sprite->_start = 1;
	}
}

void Bat::Collision()
{

}
