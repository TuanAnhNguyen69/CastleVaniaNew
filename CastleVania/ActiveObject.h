#pragma once
#include "GameObject.h"

class ActiveObject :
	public GameObject
{
public:
	ActiveObject();
	//ActiveObject(float _posX, float _posY, int _width, int _height, float _vX, float _vY, EnumID id);
	ActiveObject(float _x, float _y, float _vX, float _vY, EnumID id);
	~ActiveObject();

	virtual void Update(int dt);

	virtual void Draw(GCamera* camera);

	virtual Box GetBox();

	//Tra ve gia tri the hien Object co o trong man hinh khong
	bool IntoScreen(float _posX, float _posY, GCamera* camera);

	//Va cham, chua dinh nghia
	virtual void Collision(list<GameObject*> &obj, int dt);
};

