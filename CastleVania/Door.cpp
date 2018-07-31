#include "Door.h"



Door::Door()
{
}

Door::Door(float _posX, float _posY, int _width, int _height) :
	GameObject(_posX, _posY, EnumID::Door_ID)
{
	width = _width;
	height = _height;
	isOpen = false;
	sprite = new GSprite(TextureManager::getInstance()->getTexture(EnumID::Door_ID), 0, 3, 1000);
}

Door::~Door()
{
}
