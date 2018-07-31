#pragma once
#include "ActiveObject.h"
#include "EnumManager.h"
#include <time.h>
#include <random>

class RewardItem :
	public GameObject
{
	EnumID typeReward;
	int lifeTime;

public:
	RewardItem();

	//Khoi tao RewardItem khong phai la Crown
	RewardItem(float _x, float _y, EnumID _typeReward);
	//Khoi tao RewardItem Crown
	~RewardItem();

	void Update(int deltaTime);

	//Va cham, chua dinh nghia
	void Coliision();
};

