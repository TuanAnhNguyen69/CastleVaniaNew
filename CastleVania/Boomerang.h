#pragma once
#include "Weapon.h"

#define BOOMERANG_RAGE 150				//Tam bay cua Boomerang
#define BOOMERANG_LIFE_TIME 150			//Thoi gian ton tai cua Boomerang
#define BOOMERANG_SPEED 0.6f

class Boomerang :
	public Weapon
{
public:
	int range;
	float x0;
	bool isLeft;
	Boomerang();
	Boomerang(float _posX, float _posY, float _direction);
	~Boomerang();

	void Update(int deltaTime);

	//Va cham, chua dinh nghia
	void Collision(list<GameObject*> &obj, int dt);


};

