#include "Trap.h"



Trap::Trap() : GameObject()
{
}

Trap::Trap(float _posX, float _posY, float _max, float _min, 
	float _vUp, float _vDown, int _animationRate)
	: GameObject(_posX, _posY, EnumID::Trap_ID)
{
	vX = 0;
	vY = TRAP_SPEED_UP;
	active = true;
	vUp = _vUp;
	vDown = _vDown;
	max = _max - height / 2;
	min = _min + height / 2;
	animationRate = _animationRate;
}

Trap::~Trap()
{
}

void Trap::GoUp()
{
	vY = vUp;
}

void Trap::GoDown()
{
	vY = -vDown;
}

int Trap::Round(float _number)
{
	int result = (int)_number;
	int temp = _number * 10;
	if (abs(temp % 10) >= 5)
		result = result + abs(_number) / _number;
	return result;
}

int Trap::CheckBound()
{
	if (posY <= min)
		return -1;
	if (posY >= max)
		return 1;
	return 0;
}

void Trap::Update(int deltaTime)
{
	//chua dinh nghia
}

void Trap::Draw(GCamera* camera)
{
	//chua dinh nghia
}

void Trap::Collision()
{
	//chua dinh nghia
}