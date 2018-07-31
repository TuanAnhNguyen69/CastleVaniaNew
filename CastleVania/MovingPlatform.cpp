#include "MovingPlatform.h"



MovingPlatform::MovingPlatform() : ActiveObject()
{
}

MovingPlatform::MovingPlatform(float x, float y) : ActiveObject(x, y, 0.1f, 0, EnumID::MovingPlatform_ID)
{
	active = true;
	sprite = new GSprite(TextureManager::getInstance()->getTexture(EnumID::MovingPlatform_ID), 0, 0, 1000);
}


MovingPlatform::~MovingPlatform()
{
}

void MovingPlatform::Draw(GCamera* camera)
{
	//chua dinh nghia
}