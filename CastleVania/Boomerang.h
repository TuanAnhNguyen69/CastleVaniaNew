#pragma once
#include "Weapon.h"

#define BOOMERANG_RAGE 150				//Tam bay cua Boomerang
#define BOOMERANG_LIFE_TIME 150			//Thoi gian ton tai cua Boomerang

class Boomerang :
	public Weapon
{
public:
	Boomerang();
	Boomerang(float _posX, float _posY, int _width, int _height, float _direction);
	~Boomerang();

	void Update(int deltaTime);

	//Va cham, chua dinh nghia
	void Collision();
};

