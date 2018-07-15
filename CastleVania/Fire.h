#pragma once
#include "GameObject.h"
#include "EnumManager.h"

//Lua ban ra tu Bone Pillar
class Fire :
	public GameObject
{
	int lifeTime;
public:
	Fire();
	Fire(float _posX, float _poxY, EnumID id);
	~Fire();
	void Update(int deltaTime);
	void Draw(GCamera *camera);
	void Collision(list<GameObject*> obj, int deltaTime);
};

