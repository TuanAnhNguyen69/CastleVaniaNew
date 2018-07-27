#include "GameObject.h"
#include "Tele.h"

Tele::Tele()
{
}

Tele::Tele(float _posX, float _posY, int _width, int _height) : GameObject(_posX, _posY, _width, _height, EnumID::Tele_ID) 
{
	width = _width;
	height = _height;
	sprite = new GSprite(TextureManager::getInstance()->getTexture(EnumID::StairUpLeft_ID), 0, 0, 1000);

}

Tele::~Tele()
{
}
