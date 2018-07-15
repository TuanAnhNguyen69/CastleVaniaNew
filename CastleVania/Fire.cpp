#include "Fire.h"



Fire::Fire()
{
}

Fire::Fire(float _posX, float _posY, EnumID id) :
	GameObject(_posX, _posY, id)
{
	lifeTime = 0;
	active = true;
	canBeKilled = true;
	damage = 4;
	type = ObjectType::Enemy_Type;
}


Fire::~Fire()
{
}

void Fire::Update(int deltaTime)
{
	lifeTime += deltaTime;
	posX -= vX * deltaTime;
	if (lifeTime >= 3000) active = false;
}

void Fire::Draw(GCamera *camera)
{
	//Chua dinh nghia
}

void Fire::Collision(list<GameObject*> obj, int deltaTime)
{
	//Chua dinh nghia
}