#include "Stair.h"



Stair::Stair() : GameObject()
{
}

Stair::Stair(float _posX, float _posY, int _width, int _height, EnumID _id) :
	GameObject(_posX, _posY, _id)
{
	width = _width;
	height = _height;
	sprite = new GSprite(TextureManager::getInstance()->getTexture(_id), 0, 0, 1000);
	switch (_id)
	{
	case StairLeft_ID:
		type = EStairType::Left;
		break;
	case StairRight_ID:
		type = EStairType::Right;
		break;
	case StairTopLeft_ID:
		type = EStairType::TopLeft;
		break;
	case StairTopRight_ID:
		type = EStairType::TopRight;
		break;
	case StairBotLeft_ID:
		type = EStairType::BotLeft;
		break;
	default:
		type = EStairType::BotRight;
		break;
	}
}


Stair::~Stair()
{
}
