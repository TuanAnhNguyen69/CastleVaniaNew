#include "Panther.h"



Panther::Panther() : ActiveObject()
{
	active = true;
}

Panther::Panther(float _posX, float _posY)
	: ActiveObject(_posX, _posY, PANTHER_SPEED, 0, EnumID::Panther_ID)
{
	active = true;
	canBeKilled = true;
	type = ObjectType::Enemy_Type;
}
Panther::~Panther()
{
}

void Panther::Draw(GCamera* camera)
{
	ActiveObject::Draw(camera);
}

void Panther::Update(int deltaTime)
{
	//Chua dinh nghia
}

void Panther::Collision()
{
	//Chua dinh nghia
}