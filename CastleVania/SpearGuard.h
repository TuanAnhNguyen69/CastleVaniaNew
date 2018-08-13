#pragma once
#include "Enemy.h"

#define SPEARGUARD_SPEED 0.3f
#define SPEARGUARD_RANGE 100

class SpearGuard :
	public Enemy
{
public:

	//int posX0;
	int x0;


	void Update(int dt);
	void Draw(GCamera* camera);

	SpearGuard();
	//SpearGuard(float _posX, float _posY, int _width, int _height);
	SpearGuard(float _x, float _y);
	~SpearGuard();

	void Collision(list<GameObject*> obj, int dt);
};

