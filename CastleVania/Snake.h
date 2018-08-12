#pragma once
#include "Enemy.h"

#define SNAKE_SPEED 0.6f

class Snake :
	public Enemy
{
public:
	
	int lifeTime;

	Snake();
	Snake(float _x, float _y, float _direction);
	~Snake();
	void Draw(GCamera* camera);
	void Update(int dt);

	//Va cham, chua dinh nghia
	void Collision(list<GameObject*> &obj, int dt);
	void CollSimon(GameObject* simon, int dt);
};

