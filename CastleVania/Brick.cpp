#include "Brick.h"



Brick::Brick() : GameObject()
{
}

Brick::Brick(float _posX, float _posY, bool breakable) :
	GameObject(_posX, _posY, EnumID::Brick_ID)
{
	width = height = 32;
	isBreakable = breakable;
	sprite = new GSprite(TextureManager::getInstance()->getTexture(EnumID::Brick_ID), 0, 2, 50);
}

Brick::~Brick()
{
}

