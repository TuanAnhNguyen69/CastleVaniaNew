#pragma once
#include "Weapon.h"

#define AXE_ANPHA 45			//Góc ném
#define AXE_SPEED 0.5f			//Tốc độ ném
#define G 0.01f					//Trọng lượng Axe

class Axe :
	public Weapon
{
public:
	float x0;
	float y0;

	Axe();
	Axe(float _x, float _y, float _direction);
	~Axe();

	void FlightPath(int dt);
	void Update(int dt);
};

