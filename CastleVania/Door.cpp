#include "Door.h"



Door::Door()
{
}

Door::Door(float _posX, float _posY, int _width, int _height) :
	GameObject(_posX, _posY, _width, _height, EnumID::Door_ID)
{
	isOpen = false;
	sprite = new GSprite(TextureManager::getInstance()->getTexture(EnumID::Door_ID), 0, 3, 1000);
}

Door::~Door()
{
}
