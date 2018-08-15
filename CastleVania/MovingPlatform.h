#pragma once
#include "ActiveObject.h"
class MovingPlatform :
	public ActiveObject
{
public:
	MovingPlatform();
	MovingPlatform(float x, float y);
	~MovingPlatform();
	void Update(int dt);
	void Draw(GCamera* camera);
	void Collision(list<GameObject*> &obj, int dt);
};

