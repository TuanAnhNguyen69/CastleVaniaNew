#pragma once
#include "Enemy.h"

#define PI 3.14f
#define T 1000
#define A 10

class Ghost :
	public Enemy
{
public:
	float posY0;
	float deltaPhi;

	Ghost();
	Ghost(float _x, float _y);
	~Ghost();
	void Update(int dt);
};

