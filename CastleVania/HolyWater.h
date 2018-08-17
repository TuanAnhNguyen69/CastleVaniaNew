#pragma once
#include "Weapon.h"
#include "Sound.h"
#define HOLYWATER_ALPHA 45
#define HOLYWATER_SPEED 0.5
#define G 0.01f

class HolyWater :
	public Weapon
{
public:

	float x0;
	float y0;

	float timeBurn;
	bool isBroken;

	GSprite* spriteBroken;
	GSprite* spriteThrow;

	HolyWater();
	HolyWater(float _xSimon, float _ySimon, float _direction);
	~HolyWater();

	void FlightPath(int dt);
	void Update(int dt);

	void Collision(list<GameObject*> &obj, int dt);
};

