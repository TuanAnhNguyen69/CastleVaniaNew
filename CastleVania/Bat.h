#pragma once
#include "ActiveObject.h"

#define BAT_DAMAGE 2
#define BAT_HP 1
#define BAT_POINT 200
#define BAT_SPEED 0.2f

class Bat :
	public ActiveObject
{
public:
	bool getUp;

	Bat();
	//Bat(float _posX, float _posY, int _width, int _height);
	Bat(float _x, float _y, int _width, int _height);
	~Bat();

	void MovePath(int deltaTime);
	void Draw(GCamera* camera);
	void Update(int deltaTime);

	//void SetActive(float _posX_Simon, float _posY_Simon);
	void SetActive(float _x_Simon, float _y_Simon);

	//Va cham, chua dinh nghia
	void Collision();
};

