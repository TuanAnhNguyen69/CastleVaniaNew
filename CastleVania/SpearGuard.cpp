#include "SpearGuard.h"



SpearGuard::SpearGuard() : ActiveObject()
{
}

/*
SpearGuard::SpearGuard(float _posX, float _posY, int _width, int _height) : ActiveObject(_posX, _posY, _width, _height, SPEARGUARD_SPEED, 0, EnumID::SpearGuard_ID)
{
	active = true;
	hp = 3;
	point = 500;
	canBeKilled = true;
	type = ObjectType::Enemy_Type;
	sprite = new GSprite(TextureManager::getInstance()->getTexture(EnumID::SpearGuard_ID), 0, 3, 1000);
	posX0 = posX;
}
*/

SpearGuard::SpearGuard(float _x, float _y) 
	: ActiveObject(_x, _y, SPEARGUARD_SPEED, 0, EnumID::SpearGuard_ID)
{
	active = true;
	hp = 3;
	damage = 3;
	point = 500;
	canBeKilled = true;
	type = ObjectType::Enemy_Type;
	sprite = new GSprite(TextureManager::getInstance()->getTexture(EnumID::SpearGuard_ID), 0, 3, 80);
	x0 = x;
}
SpearGuard::~SpearGuard()
{
}

void SpearGuard::Update(int deltaTime)
{
	x += vX * deltaTime;
	if (abs(x0 - x) >= SPEARGUARD_RANGE)
	{
		vX = -vX;
	}
	sprite->Update(deltaTime);
}



void SpearGuard::Draw(GCamera* camera)
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

Box SpearGuard::GetBox()
{
	Box box = Box(0, 0, 0,0);
	box.x = this->x;
	box.y = this->y;
	box.w = 32;
	box.h = 64;
	return box;
}