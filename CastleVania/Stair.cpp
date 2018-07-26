#include "Stair.h"



Stair::Stair() : GameObject()
{
}

Stair::Stair(float _posX, float _posY, int _width, int _height, EnumID _id) :
	GameObject(_posX, _posY, _id)
{
	width = _width;
	height = _height;
	type = _id == EnumID::StairUpLeft_ID ? EStairType::UpLeft : EStairType::UpRight;
}


Stair::~Stair()
{
}
