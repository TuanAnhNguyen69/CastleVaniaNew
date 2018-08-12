#pragma once
#include "Enemy.h"
#include "EnumManager.h"

#define SPEED_FIRE 0.3f

//Lua ban ra tu Bone Pillar
class Fire :
	public Enemy
{
	int lifeTime;
public:
	Fire();
	Fire(float _x, float _y, float _directtion);
	~Fire();
	void Update(int dt);
	void Draw(GCamera *camera);

	//Va cham, chua dinh nghia
	void CollSimon(GameObject* simon, int dt);
};

