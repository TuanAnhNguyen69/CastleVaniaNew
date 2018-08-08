#include "MedusaHead.h"



MedusaHead::MedusaHead() : ActiveObject()
{
	active = true;
}

MedusaHead::MedusaHead(float _posX, float _posY)
	: ActiveObject(_posX, _posY, MEDUSAHEAD_SPEED, 0, EnumID::MedusaHead_ID)
{
	hp = 1;
	damage = 2;
	point = 300;
	active = true;
	canBeKilled = true;
	type = ObjectType::Enemy_Type;
	sprite = new GSprite(TextureManager::getInstance()->getTexture(EnumID::MedusaHead_ID), 0, 1, 100);
}

MedusaHead::~MedusaHead()
{
}

void MedusaHead::MovePath(int deltaTime)
{
	x += vX * deltaTime;
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


void MedusaHead::Update(int deltaTime)
{
	MovePath(deltaTime);
	sprite->Update(deltaTime);
}

void MedusaHead::Collision()
{
	//Chua dinh nghia
}