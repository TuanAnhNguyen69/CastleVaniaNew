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

void Weapon::Update(int dt)
{
	if (sprite == NULL || !active)
		return;
	x += vX * dt;
	y += vY * dt;
	sprite->Update(dt);
}

void Weapon::Collision(list<GameObject*> &obj, int dt)
{
	list<GameObject*>::iterator it;
	for (it = obj.begin(); it != obj.end(); it++)
	{
		GameObject* other = (*it);

		Box box = this->GetBox();
		Box boxOther = other->GetBox();
		box.vx -= boxOther.vx;
		box.vy -= boxOther.vy;
		Box broadphasebox = getSweptBroadphaseBox(box, dt);

		if (other->active) {
			if (other->type == ObjectType::Enemy_Type)
			{
				if (AABBCheck(broadphasebox, boxOther))
				{
					if (other->id == EnumID::Medusa_ID)
					{
						MedusaBoss* ms = (MedusaBoss*)other;
						if (ms->getUp)
						{
							other->ReceiveDamage(this->damage);
							if (other->hp <= 0)
							{
								point += other->point;
							}
						}
						else {
							ms->getUp = true;
						}
					}
					else
					{
						other->ReceiveDamage(this->damage);
						if (other->hp <= 0)
						{
							point += other->point;
							//other->active = false;
						}

					}
				}
			}
		}
	}
}