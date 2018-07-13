#include "Candle.h"



Candle::Candle() : GameObject()
{
}

Candle::Candle(float _posX, float _posY) :
	GameObject(_posX, _posY, EnumID::Candle_ID)
{
	canBeKilled = true;
	hp = 1;
	point = 5;
}


Candle::~Candle()
{
}
