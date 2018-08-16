#pragma once
#include "ActiveObject.h"
#include "EnumManager.h"

class SpiritBall :
	public ActiveObject
{
public:
	bool isGround;
	SpiritBall();
	SpiritBall(float _x, float _y);
	~SpiritBall();
	void Draw(GCamera* camera);
	void Update(int dt);
	void Collision(list<GameObject*> &obj, int dt);
};

