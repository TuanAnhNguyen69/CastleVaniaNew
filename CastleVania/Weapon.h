#pragma once
#include "ActiveObject.h"
#include "GSprite.h"
#include "GTexture.h"
#include <vector>

class Weapon :
	public ActiveObject
{

public:
	Weapon();
	Weapon(float _posX, float _posY, float _direction, EnumID id);
	~Weapon();

	virtual void Draw(GCamera* cammera);
	virtual void Update(int deltaTime);

	//Va cham, chua dinh nghia
	virtual void Collision(list<GameObject*> &obj, int dt);
};

