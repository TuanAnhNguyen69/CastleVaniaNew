#pragma once
#include "ActiveObject.h"

#define PANTHER_JUMP_HEIGHT 20.0f
#define PANTHER_SPEED 0.4f
#define PANTHET_JUMP_SPEED 0.3f

class Panther :
	public ActiveObject
{
public:

	bool isGrounding;
	bool isJump;

	Panther();
	Panther(float _posX, float _posY);
	~Panther();

	void Draw(GCamera* camera);

	//Chua dinh nghia
	void Update(int deltaTime);

	//Xet dieu kien hoat dong
	void SetActive(float _posX_Simon, float _posY_Siomon);

	//Hanh dong nhay
	void Jump();


	//Va cham, chua dinh nghia
	void Collision();
};

