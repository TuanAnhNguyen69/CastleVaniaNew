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
		stairType = EStairType::Left;
		break;
	case StairRight_ID:
		stairType = EStairType::Right;
		break;
	case StairTopLeft_ID:
		stairType = EStairType::TopLeft;
		break;
	case StairTopRight_ID:
		stairType = EStairType::TopRight;
		break;
	case StairBotLeft_ID:
		stairType = EStairType::BotLeft;
		break;
	default:
		stairType = EStairType::BotRight;
		break;
	}
}


Stair::~Stair()
{
}
