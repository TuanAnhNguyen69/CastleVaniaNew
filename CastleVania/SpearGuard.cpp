#include "SpearGuard.h"



SpearGuard::SpearGuard() : ActiveObject()
{
}

SpearGuard::SpearGuard(float _posX, float _posY) : ActiveObject(_posX, _posY, SPEARGUARD_SPEED, 0, EnumID::SpearGuard_ID)
{
	active = true;
	hp = 3;
	point = 500;
	canBeKilled = true;
	type = ObjectType::Enemy_Type;
}

SpearGuard::~SpearGuard()
{
}
