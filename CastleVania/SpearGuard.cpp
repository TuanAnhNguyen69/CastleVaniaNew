#include "SpearGuard.h"



SpearGuard::SpearGuard() : ActiveObject()
{
}

SpearGuard::SpearGuard(float _posX, float _posY, int _width, int _height) : ActiveObject(_posX, _posY, _width, _height, SPEARGUARD_SPEED, 0, EnumID::SpearGuard_ID)
{
	active = true;
	hp = 3;
	point = 500;
	canBeKilled = true;
	type = ObjectType::Enemy_Type;
	sprite = new GSprite(TextureManager::getInstance()->getTexture(EnumID::SpearGuard_ID), 0, 3, 1000);

}

SpearGuard::~SpearGuard()
{
}
