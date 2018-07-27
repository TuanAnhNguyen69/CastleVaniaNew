#pragma once
#include "ActiveObject.h"

#define PI 3.14f
#define T 1000
#define A 10

class Ghost :
	public ActiveObject
{
public:
	float posY0;
	float deltaPhi;

	Ghost();
	Ghost(float _posX, float _posY, int _width, int _height);
	~Ghost();
	void Update(int deltaTime);
};

