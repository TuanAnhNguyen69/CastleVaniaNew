#pragma once
#include "ActiveObject.h"
class MovingPlatform :
	public ActiveObject
{
public:
	MovingPlatform();
	MovingPlatform(float x, float y);
	~MovingPlatform();
	void Draw(GCamera* camera);
};

