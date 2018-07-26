#pragma once
#include "ActiveObject.h"
#include "EnumManager.h"
#include <time.h>
#include <random>

class RewardItem :
	public ActiveObject
{
	EnumID typeReward;
	int lifeTime;

public:
	RewardItem();

	//Khoi tao RewardItem khong phai la Crown
	RewardItem(float _posX, float _posY, EnumID _typeReward);
	RewardItem(float _posX, float _posY, int _width, int _height, EnumID _typeReward);
	//Khoi tao RewardItem Crown
	~RewardItem();

	void Update(int deltaTime);

	//Va cham, chua dinh nghia
	void Coliision();
};

