#include "Ghost.h"

Ghost::Ghost(void) : Enemy()
{
}

Ghost::Ghost(float _x, float _y) : Enemy(_x, _y, 0.08f, 0, EnumID::Ghost_ID)
{
	type = ObjectType::Enemy_Type;
	point = 300;
	hp = 2;
	damage = 2;
	canBeKilled = true;
	posY0 = y;
	deltaPhi = 0;
	sprite = new GSprite(TextureManager::getInstance()->getTexture(EnumID::Ghost_ID), 0, 1, 1000);

}

Ghost::~Ghost(void)
{
}


void Ghost::Update(int dt)
{
	int random = rand() % 10;
	if (sprite == NULL || !active)
		return;
	if (random % 2 == 0)
	{

		x += vX * dt;
		if (x <= width + 2 || x >= G_MapWidth - (width - 2))
			vX = -vX;
		y += vY * dt;

	}
	else
	{

		x += vX * dt;
		y = posY0 + A * cos(2 * PI*dt / T + deltaPhi); // Phuong trinh chuyen dong duong hinh sin x = 2pi. t/ lamda
		deltaPhi += 2 * PI*dt / T;
	}


	sprite->Update(dt);
}
