#include "Enemy.h"



Enemy::Enemy() : ActiveObject()
{
	type = ObjectType::Enemy_Type;
}

Enemy::Enemy(float _x, float _y, float _vX, float _vY, EnumID _id) :
	ActiveObject(_x, _y, _vX, _vY, _id) 
{
	type = ObjectType::Enemy_Type;
}

Enemy::~Enemy()
{
}

void Enemy::Draw(GCamera* camera)
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

/*
void Enemy::Update(int dt)
{
	if (sprite != NULL)
		sprite->Update(deltaTime);
}
*/

void Enemy::Collision(list<GameObject*> &obj, int dt)
{

}


void Enemy::SetActive(float _xSimon, float _ySimon)
{

}

void Enemy::ReceiveDamage(int _damage)
{
	if (hp > 0) {
		hp -= _damage;
	}
	
	if (hp <= 0)
	{
		isDeath = true;
		this->active = false;
	}
		
}

void Enemy::Pause()
{

}