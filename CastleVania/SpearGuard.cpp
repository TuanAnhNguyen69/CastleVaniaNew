#include "SpearGuard.h"



SpearGuard::SpearGuard() : ActiveObject()
{
}

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

SpearGuard::~SpearGuard()
{
}

void SpearGuard::Update(int deltaTime)
{
	posX += vX * deltaTime;
	if (abs(posX0 - posX) >= SPEARGUARD_RANGE)
	{
		vX = -vX;
	}
	sprite->Update(deltaTime);
}

void SpearGuard::Draw(GCamera* camera)
{
	if (sprite == NULL || !active)
		return;
	if (posX + width / 2 <= camera->viewport.x || posX - width / 2 >= camera->viewport.x + G_ScreenWidth)
	{
		active = false;
		return;
	}
	D3DXVECTOR2 center = camera->Transform(posX, posY);
	if (vX > 0)
		sprite->DrawFlipX(center.x, center.y);
	else
		sprite->Draw(center.x, center.y);
}
