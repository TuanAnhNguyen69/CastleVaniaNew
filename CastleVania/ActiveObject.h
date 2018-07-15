#pragma once
#include "GameObject.h"
class ActiveObject :
	public GameObject
{
public:
	ActiveObject();
	ActiveObject(float _posX, float _posY, float _vX, float _vY, EnumID id);
	~ActiveObject();
	virtual void Update(int deltaTime);
	virtual void Update(Box playerBox, int deltaTime);
	virtual Box GetBox();

	virtual void Draw(GCamera* camera);
	virtual void Collision(list<GameObject*> obj, int deltaTime);

	virtual void SetActive(float _vX, float _vy);
	virtual void ReceiveDamage(int damage);
};

