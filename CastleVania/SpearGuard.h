#pragma once
#include "ActiveObject.h"

#define SPEARGUARD_SPEED 0.3f
#define SPEARGUARD_RANGE 100

class SpearGuard :
	public ActiveObject
{
public:

	//int posX0;
	int x0;


	void Update(int deltaTime);
	void Draw(GCamera* camera);

	SpearGuard();
	//SpearGuard(float _posX, float _posY, int _width, int _height);
	SpearGuard(float _x, float _y);
	~SpearGuard();

	Box GetBox();

	void Collision(list<GameObject*> &obj, int dt);
};

