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

	//Update phu thuoc vao Simon
	virtual void Update(Box playerBox, int deltaTime);

	virtual void Draw(GCamera* camera);


	virtual Box GetBox();

	//Tra ve gia tri the hien Object co o trong man hinh khong
	bool IntoScreen(float _posX, float _posY, GCamera* camera);

	//Va cham, chua dinh nghia
	virtual void Collision(list<GameObject*> obj, int dt);

	virtual void SetActive(float _vX, float _vy);
	virtual void ReceiveDamage(int damage);
};

