#pragma once
#include "ActiveObject.h"
#include "EnumManager.h"
#include <time.h>
#include <random>

class RewardItem :
	public ActiveObject
{
	//thuoc tinh quyet dinh RewardItem co phai la Crown khong
	bool isCrown;

	EnumID typeReward;

	int lifeTime;

public:
	RewardItem();

	//Khoi tao RewardItem khong phai la Crown
	RewardItem(float _posX, float _posY, EnumID _typeReward);
	//Khoi tao RewardItem Crown
	RewardItem(float _posX, float _posY, bool _isCrown);
	~RewardItem();

	void Update(int deltaTime);

	//Va cham, chua dinh nghia
	void Coliision();
};

