#pragma once
#include "ActiveObject.h"

#define ZOMBIE_RANGE 300
#define ZOMBIE_HP 1
#define ZOMBIE_DAMAGE 2
#define ZOMBIE_POINT 100
#define ZOMBIE_SPEED 0.2f

class Zombie :
	public ActiveObject
{
public:
	float x0;
	Zombie();
	Zombie(float _posX, float _posY);
	~Zombie();
	void Draw(GCamera* camera);
	void Update(int deltaTime);

	//Va cham, chua dinh nghia
	void Collision();
};

