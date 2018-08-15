#pragma once
#include "ActiveObject.h"
class Enemy :
	public ActiveObject
{
public:
	int damage;

	//virtual void Update(int dt);
	virtual void Draw(GCamera *camera);
	virtual void Collision(list<GameObject*> obj, int dt);

	virtual void ReceiveDamage(int damage);
	virtual void Pause();

	virtual void SetActive(float _xSimon, float _ySimon);

	Enemy();
	Enemy(float _x, float _y, float _vX, float _vY, EnumID _id);
	~Enemy();
};

