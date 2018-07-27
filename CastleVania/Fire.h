#pragma once
#include "ActiveObject.h"
#include "EnumManager.h"

//Lua ban ra tu Bone Pillar
class Fire :
	public ActiveObject
{
	int lifeTime;
public:
	Fire();
	Fire(float _posX, float _poxY, int _width, int _height);
	~Fire();
	void Update(int deltaTime);
	void Draw(GCamera *camera);

	//Va cham, chua dinh nghia
	void Collision();
};

