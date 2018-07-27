#include "MedusaHead.h"



MedusaHead::MedusaHead() : ActiveObject()
{
	active = true;
}

MedusaHead::MedusaHead(float _posX, float _posY, int _width, int _height)
	: ActiveObject(_posX, _posY, _width, _height, MEDUSAHEAD_SPEED, 0, EnumID::MedusaHead_ID)
{
	active = true;
	canBeKilled = true;
	type = ObjectType::Enemy_Type;
	sprite = new GSprite(TextureManager::getInstance()->getTexture(EnumID::MedusaHead_ID), 0, 1, 1000);
}

MedusaHead::~MedusaHead()
{
}

void MedusaHead::MovePath(int deltaTime)
{
	posX += vX * deltaTime;
	posY = sin(posX*3.14 / 180);
}

void MedusaHead::Draw(GCamera* camera)
{
	ActiveObject::Draw(camera);
}

void MedusaHead::Update(int deltaTime)
{
	MovePath(deltaTime);
	sprite->Update(deltaTime);
}

void MedusaHead::Collision()
{
	//Chua dinh nghia
}