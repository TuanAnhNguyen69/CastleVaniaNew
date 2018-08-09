#pragma once
#include "ActiveObject.h"
#include "EnumManager.h"

#define SPEED_FIRE 0.3f

//Lua ban ra tu Bone Pillar
class Fire :
	public ActiveObject
{
	int lifeTime;
public:
	Fire();
	Fire(float _x, float _y, float _directtion);
	~Fire();
	void Update(int deltaTime);
	void Draw(GCamera *camera);

	//Va cham, chua dinh nghia
	void Collision();
};

