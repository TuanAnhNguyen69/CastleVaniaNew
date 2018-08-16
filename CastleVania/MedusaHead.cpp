#include "MedusaHead.h"



MedusaHead::MedusaHead() : Enemy()
{
	active = true;
}

MedusaHead::MedusaHead(float _x, float _y)
	: Enemy(_x, _y, MEDUSAHEAD_SPEED, 0, EnumID::MedusaHead_ID)
{
	hp = 1;
	damage = 2;
	point = 300;
	active = true;
	canBeKilled = true;
	type = ObjectType::Enemy_Type;
	sprite = new GSprite(TextureManager::getInstance()->getTexture(EnumID::MedusaHead_ID), 0, 1, 100);
	fly = false;
}

MedusaHead::~MedusaHead()
{
}

void MedusaHead::MovePath(int dt)
{
	x += vX * dt;
	y = std::sin(x * 0.03) * 3 + y;
}


void MedusaHead::Draw(GCamera* camera)
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


void MedusaHead::Update(int dt)
{
	if(fly)
		MovePath(dt);
	sprite->Update(dt);
}

void MedusaHead::SetActive(float _xSimon, float _ySimon)
{
	if (abs(x - _xSimon) <= 200 && abs(y - _ySimon) <= 150)
	{
		fly = true;
		if (x - _xSimon > 0)
			vX = -MEDUSAHEAD_SPEED;
		else
			vX = MEDUSAHEAD_SPEED;
	}
}

void MedusaHead::Collision()
{
	//Chua dinh nghia
}