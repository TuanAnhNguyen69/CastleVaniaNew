#pragma once
#include "Enemy.h";


class PhantomBat : public Enemy {
public:
	bool getUp;
	PhantomBat();
	PhantomBat(float _posX, float _posY);
	~PhantomBat();

	void MovePath(int dt);
	void Draw(GCamera* camera);
	void Update(int dt);

	void SetActive(float _posX_Simon, float _posY_Simon);

	//Va cham, chua dinh nghia

	void Collision();

};
