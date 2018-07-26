#include "Door.h"



Door::Door()
{
}

Door::Door(float _posX, float _posY) :
	GameObject(_posX, _posY, EnumID::Door_ID)
{
	isOpen = false;
}

Door::~Door()
{
}
