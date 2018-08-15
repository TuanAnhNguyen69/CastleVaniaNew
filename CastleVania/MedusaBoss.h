#pragma once
#include "Enemy.h"
#include "Snake.h"

#define MEDUSA_SPEED 0.25f

class MedusaBoss :
	public Enemy
{
public:
	bool getUp;
	int reloadTime;

	GSprite* spriteSleep;
	GSprite* spriteAttack;

	list<ActiveObject*> *listSnake;
	bool isLeft;

	void UpdateSnake(float dt);
	void DrawSnake(GCamera* camera);

	void MovePath(int dt);
	void Draw(GCamera* camera);
	void Update(int dt);

	void Update(float _xSimon, float _ySimon, int dt);

	//void SetActive(float _x_Simon, float _y_Simon);

	//Va cham, chua dinh nghia
	void Collision(list<GameObject*> &obj, int dt);

	void CollSimon(GameObject* simon, int dt);

	Box GetBox();

	MedusaBoss();
	MedusaBoss(float _x, float _y);
	~MedusaBoss();
};

