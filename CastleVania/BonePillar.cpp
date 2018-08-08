#include "BonePillar.h"



BonePillar::BonePillar() : ActiveObject()
{
}

BonePillar::BonePillar(float _posX, float _posY, bool _isLeft) : ActiveObject(_posX, _posY, 0, 0, EnumID::BonePillar_ID)
{
	listFire = new list<ActiveObject*>();
	type = ObjectType::Enemy_Type;
	hp = 6;
	damage = 2;
	point = 400;
	active = true;
	lifeTime = 0;
	canBeKilled = true;
	isLeft = _isLeft;
	sprite = new GSprite(TextureManager::getInstance()->getTexture(EnumID::BonePillar_ID), 12);
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
			++obj;
		}
	}
}

void BonePillar::DrawFire(GCamera* camera)
{
	for (list<ActiveObject*>::iterator fire = listFire->begin(); fire != listFire->end(); fire++)
	{
		//DynamicObject* fire = (*iter);
		(*fire)->Draw(camera);
	}
}

void BonePillar::Update(int deltaTime)
{
	if(active)
	{
		lifeTime += deltaTime;
		if (lifeTime % 30 == 0)
		{
			if(isLeft)
				listFire->push_back(new Fire(x, y - 10, -1));
			else
				listFire->push_back(new Fire(x, y - 10, 1));
		}

		UpdateFire(deltaTime);

	}
}

void BonePillar::Draw(GCamera* camera)
{
	D3DXVECTOR2 pos = camera->Transform(x, y);
	if(isLeft)
		sprite->Draw(pos.x, pos.y);
	else
		sprite->DrawFlipX(pos.x, pos.y);
	this->DrawFire(camera);
}

void BonePillar::Collision()
{

}