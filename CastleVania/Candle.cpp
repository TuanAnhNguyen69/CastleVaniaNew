#include "Candle.h"



Candle::Candle() : GameObject()
{
}

Candle::Candle(float _posX, float _posY, int _width, int _height) :
	GameObject(_posX, _posY, _width, _height, EnumID::Candle_ID)
{
	canBeKilled = true;
	hp = 1;
	point = 5;
	sprite = new GSprite(TextureManager::getInstance()->getTexture(EnumID::Candle_ID), 0, 1, 1000);
}


Candle::~Candle()
{
}
