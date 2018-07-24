#include "RewardItem.h"



RewardItem::RewardItem() : ActiveObject()
{
}

RewardItem::RewardItem(float _posX, float _posY, EnumID _typeReward) :
	ActiveObject(_posX, _posY, 0, -0.4f, EnumID::RewardItem_ID)
{
	typeReward = _typeReward;
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
			/*
			if (isCrown)
			{
				point = 2000;
				id = EnumID::Crown_ID;
				sprite = new GSprite(TextureManager::getInstance()->getTexture(EnumID::Crown_ID), 150);
			}
			*/

			//Neu vu khi chua max cap
			/*
			if (simon->GetLevelWeapon() < 3)
			{
				id = EnumID::MorningStar_ID;
				sprite = new GSprite(TextureManager::getInstance()->getTexture(EnumID::MorningStar_ID), 1000);
			}
			*/
			int rd = rand() % 10;
			int percent = rand() % 100;
			if (rd < 9)
			{	
				if (percent < 60)
				{
					id = EnumID::SmallHeart_ID;
					sprite = new GSprite(TextureManager::getInstance()->getTexture(EnumID::SmallHeart_ID), 1000);
				}
				else if (percent < 70)
				{
					id = EnumID::BigHeart_ID;
					sprite = new GSprite(TextureManager::getInstance()->getTexture(EnumID::BigHeart_ID), 1000);
					hearts = 1;
				}
				else if (percent < 74)
				{
					id = EnumID::Roast_ID;
					sprite = new GSprite(TextureManager::getInstance()->getTexture(EnumID::RedMoneyBag_ID), 1000);
				}
				else if (percent < 78)
				{
					id = EnumID::RedMoneyBag_ID;
					sprite = new GSprite(TextureManager::getInstance()->getTexture(EnumID::RedMoneyBag_ID), 1000);
					point = 100;
				}
				else if (percent < 82)
				{
					id = EnumID::WhiteMoneyBag_ID;
					sprite = new GSprite(TextureManager::getInstance()->getTexture(EnumID::WhiteMoneyBag_ID), 1000);
					point = 400;
				}
				else if (percent < 86)
				{
					id = EnumID::BlueMoneyBag_ID;
					sprite = new GSprite(TextureManager::getInstance()->getTexture(EnumID::BlueMoneyBag_ID), 1000);
					point = 700;
				}
				else if (percent < 90)
				{
					id = EnumID::ExtraMoneyBag_ID;
					sprite = new GSprite(TextureManager::getInstance()->getTexture(EnumID::ExtraMoneyBag_ID), 1000);
					point = 10000;
				}
				else
				{
					id = EnumID::Cross_ID;
					sprite = new GSprite(TextureManager::getInstance()->getTexture(EnumID::Cross_ID), 1000);
				}
			}
			else
			{
				if (percent < 20)
				{
					id = EnumID::Item_Axe_ID;
					sprite = new GSprite(TextureManager::getInstance()->getTexture(EnumID::Item_Axe_ID), 1000);
				}
				else if (percent < 40)
				{
					id = EnumID::Item_Boomerang_ID;
					sprite = new GSprite(TextureManager::getInstance()->getTexture(EnumID::Item_Boomerang_ID), 1000);
				}
				else if (percent < 60)
				{
					id = EnumID::Item_HolyWater_ID;
					sprite = new GSprite(TextureManager::getInstance()->getTexture(EnumID::Item_HolyWater_ID), 1000);
				}
				else if (percent < 80)
				{
					id = EnumID::Item_Knife_ID;
					sprite = new GSprite(TextureManager::getInstance()->getTexture(EnumID::Item_Knife_ID), 1000);
				}
				else
				{
					id = EnumID::Item_StopWatch_ID ;
					sprite = new GSprite(TextureManager::getInstance()->getTexture(EnumID::Item_StopWatch_ID), 1000);
				}
			}
			
		}
	}
}

