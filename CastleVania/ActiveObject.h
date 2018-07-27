#pragma once
#include "GameObject.h"
class ActiveObject :
	public GameObject
{
public:
	ActiveObject();
	ActiveObject(float _posX, float _posY, int _width, int _height, float _vX, float _vY, EnumID id);
	~ActiveObject();
	virtual void Update(int deltaTime);
	virtual void Update(Box playerBox, int deltaTime);
	virtual Box GetBox();

	virtual void Draw(GCamera* camera);

	bool IntoScreen(float _posX, float _posY, GCamera* camera);

	//Va cham, chua dinh nghia
	virtual void Collision(list<GameObject*> obj, int dt);

	virtual void SetActive(float _vX, float _vy);
	virtual void ReceiveDamage(int damage);
};

