#include "HitEffect.h"



HitEffect::HitEffect()
{
}

HitEffect::HitEffect(float _posX, float _posY, int _width, int _height) :
	GameObject(_posX, _posY, EnumID::HitEffect_ID)
{
	width = _width;
	height = _height;
}


HitEffect::~HitEffect()
{
}
