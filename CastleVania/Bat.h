#pragma once
#include "Enemy.h"

#define BAT_DAMAGE 2
#define BAT_HP 1
#define BAT_POINT 200
#define BAT_SPEED 0.2f

class Bat :
	public Enemy
{
public:
	bool getUp;

	GSprite* spriteSleep;
	GSprite* spriteFly;

	Bat();
	//Bat(float _posX, float _posY, int _width, int _height);
	Bat(float _x, float _y);
	~Bat();

	void MovePath(int dt);
	void Draw(GCamera* camera);
	void Update(int dt);

	void SetActive(float _x_Simon, float _y_Simon);

	//Va cham, chua dinh nghia
	void Collision();
};

