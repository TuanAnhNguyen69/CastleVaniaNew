#pragma once
#include "ActiveObject.h";


class PhantomBat : public ActiveObject {
public:
	bool getUp;
	PhantomBat();
	PhantomBat(float _posX, float _posY, int _width, int _height);
	~PhantomBat();

	void MovePath(int deltaTime);
	void Draw(GCamera* camera);
	void Update(int deltaTime);

	void SetActive(float _posX_Simon, float _posY_Simon);

	//Va cham, chua dinh nghia

	void Collision();

};
