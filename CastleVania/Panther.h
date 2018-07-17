#pragma once
#include "ActiveObject.h"

#define PANTHER_JUMP_HEIGHT 20.0f
#define PANTHER_SPEED 0.2f

class Panther :
	public ActiveObject
{
public:
	Panther();
	Panther(float _posX, float _posY);
	~Panther();

	void Draw(GCamera* camera);

	//Chua dinh nghia
	void Update(int deltaTime);


	//Va cham, chua dinh nghia
	void Collision();
};

