#include "Weapon.h"

#define SPEED_WEAPON 0.5f


Weapon::Weapon() : ActiveObject()
{
	//active = true;
}

Weapon::Weapon(float _posX, float _posY, float _direction, EnumID id) :
	ActiveObject(_posX, _posY, 0, 0, id)
{
	damage = 2;
	//active = true;
	if (_direction > 0)
		vX = SPEED_WEAPON;
	else
		vX = -SPEED_WEAPON;
}


Weapon::~Weapon()
{
}

void Weapon::Draw(GCamera* camera)
{
	if (sprite == NULL || !active)
		return;
	if (x + width <= camera->viewport.x || x  >= camera->viewport.x + G_ScreenWidth)
	{
		active = false;
		return;
	}
	D3DXVECTOR2 pos = camera->Transform(x, y);
	if (vX > 0)
		sprite->Draw(pos.x, pos.y);
	else
		sprite->DrawFlipX(pos.x, pos.y);
}

void Weapon::Update(int deltaTime)
{
	if (sprite == NULL || !active)
		return;
	x += vX * deltaTime;
	y += vY * deltaTime;
	sprite->Update(deltaTime);
}

void Weapon::Collision(list<GameObject*> &obj, int dt)
{
	list<GameObject*>::iterator it;
	for (it = obj.begin(); it != obj.end(); it++)
	{
		GameObject* other = (*it);

		Box box = this->GetBox();
		Box boxOther = other->GetBox();
		Box broadphasebox = getSweptBroadphaseBox(box, dt);

		switch (other->id)
		{
		case EnumID::Bat_ID:
		case EnumID::BonePillar_ID:
		case EnumID::Fire_ID:
		case EnumID::Ghost_ID:
		case EnumID::MedusaHead_ID:
		case EnumID::Panther_ID:
		case EnumID::SpearGuard_ID:
		case EnumID::Zombie_ID:
			other->ReceiveDamage(this->damage);
			break;
		case EnumID::Simon_ID:
			if (this->id == EnumID::Boomerang_Weapon_ID)
			{
				other->sprite->SelectIndex(8);
				this->active = false;
			}	
			break;
		default:
			break;
		}
	}
}