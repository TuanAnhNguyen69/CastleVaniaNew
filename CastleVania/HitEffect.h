#pragma once
#include "GameObject.h"
#include "EnumManager.h"

class HitEffect :
	public GameObject
{
public:
	HitEffect();
	HitEffect(float _posX, float _posY);
	~HitEffect();
};

