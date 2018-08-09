#include "Axe.h"



Axe::Axe()
{
	active = true;
}

Axe::Axe(float _x, float _y, float _direction) : 
	Weapon(_x, _y, _direction, EnumID::Axe_Weapon_ID)
{
	active = true;
	damage = 4;

	if (_direction < 0)
	{
		vX = -AXE_SPEED;
		x0 = x = _x;
	}
	else
	{
		vX = AXE_SPEED;
		x0 = x = _x + 20;
	}

	y0 = y = _y;
}

Axe::~Axe()
{
}

void Axe::FlightPath(int dt)
{
	x += vX * dt;
	float dx;
	dx = abs(x - x0);

	float relaHeight	=	0.03f;			//chiều cao tương dối: càng lớn thấp (rớt nhanh hơn)
	float relaDistance	= 	4.0f;			//chiều xa tương đối : càng lớn xa 
	//y = -a*x*x + b*x + c
	y = -relaHeight * (dx*dx)  + relaDistance  * dx +y0 ;
}

void Axe::Update(int dt)
{
	if (!active)
		return;
	else
	{
		this->FlightPath(dt);
		sprite->Update(dt);
	}
}

