#pragma once
#include "ActiveObject.h"
class MovingPlatform :
	public ActiveObject
{
public:
	MovingPlatform();
	MovingPlatform(float x, float y, int _width, int _height);
	~MovingPlatform();
	void Draw(GCamera* camera);
};

