#pragma once
#include "ActiveObject.h"


class Weapon :
	public ActiveObject
{
public:
	Weapon();
	Weapon(float _posX, float _posY, float _direction, EnumID id);
	~Weapon();

	void Draw(GCamera* cammera);
	void Update(int deltaTime);

	//Va cham, chua dinh nghia
	void Collision();
};

