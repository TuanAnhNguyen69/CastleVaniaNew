#include "Zombie.h"



Zombie::Zombie() : Enemy()
{
	active = true;
}

Zombie::Zombie(float _x, float _y)
	: Enemy(_x, _y, ZOMBIE_SPEED, 0, EnumID::Zombie_ID)
{
	hp = 1;
	damage = 2;
	point = 100;
	x0 = _x;
	active = true;
	canBeKilled = true;
	type = ObjectType::Enemy_Type;
}


Zombie::~Zombie()
{
}

void Zombie::Draw(GCamera* camera)
{
	if (sprite == NULL || !active)
		return;
	if (x <= camera->viewport.x || x >= camera->viewport.x + G_ScreenWidth)
	{
		active = false;
		return;
	}
	D3DXVECTOR2 pos = camera->Transform(x, y);
	if (vX > 0)
		sprite->DrawFlipX(pos.x, pos.y);
	else
		sprite->Draw(pos.x, pos.y);
}

void Zombie::Update(int dt)
{
	x += vX * dt;
	if(abs(x - x0) > ZOMBIE_RANGE)
		vX = -vX;
	sprite->Update(dt);
}

void Zombie::Collision()
{

}