#include "Bat.h"



Bat::Bat() : Enemy()
{
	active = true;
}

Bat::Bat(float _x, float _y)
	: Enemy(_x, _y, BAT_SPEED, 0, EnumID::Bat_ID)
{
	damage = 2;
	hp = 1;
	point = 200;
	active = true;
	canBeKilled = true;
	type = ObjectType::Enemy_Type;
	getUp = false;
	spriteSleep = new GSprite(TextureManager::getInstance()->getTexture(EnumID::Bat_ID), 0, 0, 100);
	spriteFly = new GSprite(TextureManager::getInstance()->getTexture(EnumID::Bat_ID), 1, 3, 100);

	sprite = spriteSleep;
}

Bat::~Bat()
{
}

void Bat::MovePath(int dt)
{
	x += vX * dt*2;
	y = std::sin(x * 0.03)*3 + y;
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

void Bat::Update(int dt)
{
	if (active)
	{
		Dying(dt);
		if (getUp)
		{
			this->MovePath(dt);
			sprite->Update(dt);
		}
	}	
}

void Bat::SetActive(float _xSimon, float _ySimon)
{
	if (getUp)
		return;

	if (abs(x - _xSimon) <= 100 && abs(y - _ySimon) <= 100)
	{
		getUp = true;
		sprite = spriteFly;
		if (x - _xSimon > 0)
			vX = -BAT_SPEED;
		else
			vX = BAT_SPEED;
	}
}

void Bat::Collision()
{

}
