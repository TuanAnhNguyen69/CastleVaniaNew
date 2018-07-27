#include "Ghost.h"

Ghost::Ghost(void) : ActiveObject()
{
}

Ghost::Ghost(float _posX, float _posY, int _width, int _height) : ActiveObject(_posX, _posY, _width, _height, 0.08f, 0, EnumID::Ghost_ID)
{
	type = ObjectType::Enemy_Type;
	point = 300;
	hp = 2;
	damage = 2;
	canBeKilled = true;
	posY0 = posY;
	deltaPhi = 0;
	sprite = new GSprite(TextureManager::getInstance()->getTexture(EnumID::Ghost_ID), 0, 1, 1000);

}

Ghost::~Ghost(void)
{
}


void Ghost::Update(int deltaTime)
{
	int random = rand() % 10;
	if (sprite == NULL || !active)
		return;
	if (random % 2 == 0)
	{

		posX += vX * deltaTime;
		if (posX <= width / 2 + 2 || posX >= G_MapWidth - (width / 2 - 2))
			vX = -vX;
		posY += vY * deltaTime;

	}
	else
	{

		posX += vX * deltaTime;
		posY = posY0 + A * cos(2 * PI*deltaTime / T + deltaPhi); // Phuong trinh chuyen dong duong hinh sin x = 2pi. t/ lamda
		deltaPhi += 2 * PI*deltaTime / T;
	}


	sprite->Update(deltaTime);
}
