#include "Fire.h"



Fire::Fire()
{
}

Fire::Fire(float _posX, float _posY, int _width, int _height) :
	ActiveObject(_posX, _posY, _width, _height, 0.5f, 0, EnumID::Fire_ID)
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
	x -= vX * deltaTime;
	if (lifeTime >= 3000) active = false;
}

void Fire::Draw(GCamera *camera)
{
	ActiveObject::Draw(camera);
}

void Fire::Collision()
{
	//Chua dinh nghia
}