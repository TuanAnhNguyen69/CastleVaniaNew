#include "RewardItem.h"



RewardItem::RewardItem() : GameObject()
{
}

RewardItem::RewardItem(float _posX, float _posY, EnumID _typeReward) :
	GameObject(_posX, _posY, _typeReward)
{
	typeReward = _typeReward;
	lifeTime = 0;
	active = true;
	type = ObjectType::Item;
	id = _typeReward;
	sprite = new GSprite(TextureManager::getInstance()->getTexture(_typeReward), 1000);
	point = 1000;
}

RewardItem::RewardItem(float _posX, float _posY, int _width, int _height, EnumID _typeReward) : GameObject(_posX, _posY, _typeReward)
{
	typeReward = _typeReward;
	lifeTime = 0;
	active = true;
	type = ObjectType::Item;
	width = _width;
	height = _height;
	id = _typeReward;
	sprite = new GSprite(TextureManager::getInstance()->getTexture(_typeReward), 1000);
	point = 1000;
}

RewardItem::~RewardItem()
{

}

void RewardItem::Update(int deltaTime)
{
	if (sprite == NULL)
		return;
	posY += vY * deltaTime;
	lifeTime += deltaTime;
	//Xu ly thoi gian ton tai cua RewardItem
	if (lifeTime > 1500)
		this->Remove();
	sprite->Update(deltaTime);
}

