#pragma once
#include "ActiveObject.h"
class Snake :
	public ActiveObject
{
public:
	Snake();
	Snake(float _posX, float _posY, float _vX, float _vY, EnumID id);
	~Snake();
	void Draw(GCamera* camera);

	//Va cham, chua dinh nghia
	void Collision();
};

