#pragma once
#include "Enemy.h"

#define PANTHER_JUMP_HEIGHT 20.0f
#define PANTHER_SPEED 0.4f
#define PANTHET_JUMP_SPEED 0.3f

class Panther :
	public Enemy
{
public:

	bool isGrounding;
	bool isJump;
	bool hasJump;			//Đã thực hiện trạng thái nhảy hay chưa

	Panther();
	Panther(float _posX, float _posY);
	~Panther();

	void Draw(GCamera* camera);

	//Chua dinh nghia
	void Update(int dt);

	//Xet dieu kien hoat dong
	void SetActive(float _posX_Simon, float _posY_Siomon);

	//Hanh dong nhay
	void Jump();


	//Va cham, chua dinh nghia
	void Collision(list<GameObject*> &obj, int dt);
};

