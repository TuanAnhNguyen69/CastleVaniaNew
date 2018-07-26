#include "GameObject.h"
#include "Tele.h"

Tele::Tele()
{
}

Tele::Tele(float _posX, float _posY, int _width, int _height) : GameObject(_posX, _posY, EnumID::Tele_ID) 
{
	width = _width;
	height = _height;
}

Tele::~Tele()
{
}
