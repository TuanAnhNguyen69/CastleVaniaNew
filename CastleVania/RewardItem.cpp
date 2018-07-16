#include "RewardItem.h"



RewardItem::RewardItem() : ActiveObject()
{
}

RewardItem::RewardItem(float _posX, float _posY) :
	ActiveObject(_posX, _posY, 0, -0.4f, EnumID::RewardItem_ID)
{
	lifeTime = 0;
	active = true;
	type = ObjectType::Item;
	isCrown = false;
}


RewardItem::RewardItem(float _posX, float _posY, bool _isCrown) :
	ActiveObject(_posX, _posY, 0, -0.4f, EnumID::RewardItem_ID)
{
	lifeTime = 0;
	active = true;
	type = ObjectType::Item;
	isCrown = _isCrown;
}

RewardItem::~RewardItem()
{
}

void RewardItem::Update(int deltaTime)
{
	if (sprite == NULL)
		return;
	if (id != EnumID::RewardItem_ID)
	{
		posY += vY * deltaTime;
		lifeTime += deltaTime;
		//Xu ly thoi gian ton tai cua RewardItem
		if (lifeTime > 1500)
			this->Remove();
	}
	else
	{
		sprite->Update(deltaTime);

		if (sprite->GetIndex() == 2)
		{
			//Neu la Crown
			if (isCrown)
			{
				point = 2000;
				id = EnumID::Crown_ID;
				sprite = new GSprite(TextureManager::getInstance()->getTexture(EnumID::Crown_ID), 150);
			}

		}
	}
}

