#include "BonePillar.h"



BonePillar::BonePillar() : ActiveObject()
{
}

BonePillar::BonePillar(float _posX, float _posY) : ActiveObject(_posX, _posY, 0, 0, EnumID::BonePillar_ID)
{
	listFire = new list<ActiveObject*>();
	type = ObjectType::Enemy_Type;
	hp = 8;
	active = true;
	lifeTime = 0;
	canBeKilled = true;
}

BonePillar::~BonePillar()
{
	delete listFire;
}

void BonePillar::UpdateFire(float deltaTime)
{
	list<ActiveObject*>::iterator obj = listFire->begin();
	while (obj != listFire->end())
	{
		if (!(*obj)->active)
			listFire->erase(obj++);
		else
		{
			(*obj)->Update(deltaTime);
			obj++;
		}
	}
}

void BonePillar::DrawFire(GCamera* camera)
{
	list<ActiveObject*>::iterator obj = listFire->begin();
	while (obj != listFire->end())
	{
		(*obj)->Draw(camera);
		obj++;
	}
}

void BonePillar::Update(int deltaTime)
{
	if(active)
	{
		lifeTime += deltaTime;
		if (lifeTime % 30 == 0)
		{
			listFire->push_back(new Fire(posX, posY + 10, EnumID::Fire_ID));
		}

		UpdateFire(deltaTime);

	}
}

void BonePillar::Draw(GCamera* camera)
{
	D3DXVECTOR2 center = camera->Transform(posX, posY);
	sprite->Draw(center.x, center.y);
	this->DrawFire(camera);
}

void BonePillar::Collision()
{

}