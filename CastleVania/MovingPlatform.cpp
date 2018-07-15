#include "MovingPlatform.h"



MovingPlatform::MovingPlatform() : ActiveObject()
{
}

MovingPlatform::MovingPlatform(float x, float y) : ActiveObject(x, y, 0.1f, 0, EnumID::MovingPlatform_ID)
{
	active = true;
}


MovingPlatform::~MovingPlatform()
{
}

void MovingPlatform::Draw(GCamera* camera)
{
	//chua dinh nghia
}