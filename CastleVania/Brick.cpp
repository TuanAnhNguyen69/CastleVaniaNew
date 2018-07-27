#include "Brick.h"



Brick::Brick() : GameObject()
{
}

Brick::Brick(float _posX, float _posY, int _width, int _height, bool breakable) :
	GameObject(_posX, _posY, _width, _height, EnumID::Brick_ID)
{
	isBreakable = breakable;
	sprite = new GSprite(TextureManager::getInstance()->getTexture(EnumID::Brick_ID), 0, 0, 1000);

}

Brick::~Brick()
{
}

