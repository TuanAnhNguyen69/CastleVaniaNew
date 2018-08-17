#include "HolyWater.h"



HolyWater::HolyWater()
{
}

HolyWater::HolyWater(float _xSimon, float _ySimon, float _direction) :
	Weapon(_xSimon, _ySimon, _direction, EnumID::HolyWater_Weapon_ID)
{
	spriteBroken = new GSprite(TextureManager::getInstance()->getTexture(id), 1, 2, 16);
	spriteThrow = new GSprite(TextureManager::getInstance()->getTexture(id), 0, 0, 16);
	isBroken = false;

	timeBurn = 0;

	active = true;
	damage = 4;

	if (_direction < 0)
	{
		vX = -HOLYWATER_SPEED;
		x0 = x = _xSimon;
	}
	else
	{
		vX = HOLYWATER_SPEED;
		x0 = x = _xSimon + 20;
	}

	y0 = y = _ySimon;
}

HolyWater::~HolyWater()
{
}

void HolyWater::FlightPath(int dt)
{
	x += vX * dt;
	float dx = abs(x - x0);

	float relaHeight = 0.03f;			//chiều cao tương dối: càng lớn thấp (rớt nhanh hơn)
	float relaDistance = 2.0f;			//chiều xa tương đối : càng lớn xa 

	//y = -a*x*x + b*x + c
	y = -relaHeight * (dx*dx) + relaDistance * dx + y0;
}

void HolyWater::Update(int dt)
{
	if (!isBroken)
	{
		this->FlightPath(dt);
		//sprite->SelectIndex(0);
		spriteThrow->Update(dt);
	}
	else
	{
		timeBurn += dt;
		sprite = spriteBroken;
		sprite->Update(dt);
		if (timeBurn > 500)
			active = false;
	}
		
		//sprite = spriteBroken;
		//spriteBroken->Update(dt);

	
	
}

void HolyWater::Collision(list<GameObject*> &obj, int dt)
{
	list<GameObject*> listObject;
	list<GameObject*>::iterator it;
	for (it = obj.begin(); it != obj.end(); it++)
	{
		GameObject* other = (*it);

		Box box = this->GetBox();
		Box boxOther = other->GetBox();
		Box broadphasebox = getSweptBroadphaseBox(box, dt);
		if (AABBCheck(broadphasebox, boxOther))
		{
			ECollisionDirection colDirection;
			float collisionTime = sweptAABB(box, boxOther, colDirection, dt);
			if (collisionTime < 1.0f && collisionTime > 0.0)
			{
				switch (other->id)
				{
				case EnumID::Brick_ID:
					this->isBroken = true;
					this->y = other->y + this->height;
					//this->y += this->vY * collisionTime * dt;
					this->vY = 0;
					sound->PlayEffectSound(EEffectSound::EHolyWaterSound);
					//Sound::GetInstance()->PlayEffectSound(EEffectSound::EHolyWaterSound);
					break;
				default:
					break;
				}
			}
		}
	}
}

