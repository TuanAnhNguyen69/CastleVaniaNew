#include "Bat.h"



Bat::Bat() : ActiveObject()
{
	active = true;
}

/*
Bat::Bat(float _posX, float _posY, int _width, int _height)
	: ActiveObject(_posX, _posY, _width, _height, BAT_SPEED, 0, EnumID::Bat_ID)
{
	active = true;
	canBeKilled = true;
	type = ObjectType::Enemy_Type;
	getUp = false;
	sprite = new GSprite(TextureManager::getInstance()->getTexture(EnumID::Bat_ID), 1, 3, 100);
}
*/

Bat::Bat(float _x, float _y, int _width, int _height)
	: ActiveObject(_x, _y, _width, _height, BAT_SPEED, 0, EnumID::Bat_ID)
{
	active = true;
	canBeKilled = true;
	type = ObjectType::Enemy_Type;
	getUp = false;
	sprite = new GSprite(TextureManager::getInstance()->getTexture(EnumID::Bat_ID), 1, 3, 100);
}

Bat::~Bat()
{
}

void Bat::MovePath(int deltaTime)
{
	//posX += vX * deltaTime;
	x += vX * deltaTime;
}

void Bat::Draw(GCamera* camera)
{
	if (sprite == NULL || !active)
		return;
	//if (posX + width / 2 <= camera->viewport.x || posX - width / 2 >= camera->viewport.x + G_ScreenWidth)
	if (x <= camera->viewport.x || x >= camera->viewport.x + G_ScreenWidth)
	{
		active = false;
		return;
	}
	/*
	D3DXVECTOR2 center = camera->Transform(posX, posY);
	if (vX > 0)
		sprite->DrawFlipX(center.x, center.y);
	else
		sprite->Draw(center.x, center.y);
	*/
	D3DXVECTOR2 pos = camera->Transform(x, y);
	if (vX > 0)
		sprite->DrawFlipX(pos.x, pos.y);
	else
		sprite->Draw(pos.x, pos.y);
}

void Bat::Update(int deltaTime)
{
	// (getUp)
	{
		this->MovePath(deltaTime);
		sprite->Update(deltaTime);
	}
	/*
	if (hp <= 0)
	{
		Score += point;
		isDeath = true;
		return;
	}
	*/
	
}

void Bat::SetActive(float _x_Simon, float _y_Simon)
{
	getUp = true;
	vX = BAT_SPEED;
	/*
	if (abs(posX - _posX_Simon) <= 300 && abs(posY - _posY_Simon) <= 300)
	{
		getUp = true;
		if (posX - _posX_Simon > 0)
			vX = -BAT_SPEED;
		else
			vX = BAT_SPEED;
		sprite->_start = 1;
	}
	*/
	
}

void Bat::Collision()
{

}
