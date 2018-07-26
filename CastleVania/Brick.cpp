#include "Brick.h"



Brick::Brick() : GameObject()
{
}

Brick::Brick(float _posX, float _posY, int _width, int _height, bool breakable) :
	GameObject(_posX, _posY, EnumID::Brick_ID)
{
	isBreakable = breakable;
	width = _width;
	height = _height;
}

Brick::~Brick()
{
}

