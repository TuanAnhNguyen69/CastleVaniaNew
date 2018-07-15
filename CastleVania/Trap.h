#pragma once
#include "GameObject.h"
#include "EnumManager.h"


//Bay chong

#define TRAP_RATE 4

#define TRAP_SPEED_UP 0.03f
#define TRAP_SPEED_DOWN 0.1f
#define TRAP_MAX 1040
#define TRAP_MIN 900

class Trap :
	public GameObject
{
protected:
	float vUp;
	float vDown;
	float max;
	float min;
	int animationRate;

	int Round(float _number);
	int CheckBound();
	void GoUp();
	void GoDown();
public:
	Trap();
	Trap(float _posX, float _posY, float _max = TRAP_MAX, float _min = TRAP_MIN, 
	float _vUp = TRAP_SPEED_UP, float _vDown = TRAP_SPEED_DOWN, int _animationRate = TRAP_RATE);
	~Trap();
	void Update(int deltaTime);
	void Draw(GCamera* camera);
	void Collision(list<GameObject*> obj, int deltaTime);
};

