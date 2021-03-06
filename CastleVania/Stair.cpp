#include "Stair.h"



Stair::Stair() : GameObject()
{
}

Stair::Stair(float _posX, float _posY, int _width, int _height, EnumID _id) :
	GameObject(_posX, _posY, _width, _height, _id)
{
	width = _width;
	height = _height;
	type = _id == EnumID::StairUpLeft_ID ? EStairType::UpLeft : EStairType::UpRight;
	sprite = new GSprite(TextureManager::getInstance()->getTexture(EnumID::StairUpLeft_ID), 0, 0, 1000);

}


Stair::~Stair()
{
}
