#include "RewardItem.h"



RewardItem::RewardItem() : GameObject()
{
}

RewardItem::RewardItem(float _x, float _y, EnumID _typeReward) : GameObject(_x, _y, _typeReward)
{
	typeReward = _typeReward;
	lifeTime = 0;
	active = true;
	type = ObjectType::Item;
	id = _typeReward;
	//sprite = new GSprite(TextureManager::getInstance()->getTexture(_typeReward), 1000);
	spriteNull = NULL;
	spriteDrop = new GSprite(TextureManager::getInstance()->getTexture(_typeReward), 1000);
	vY = -1.0f;
	isDrop = false;
	isGround = false;
}

RewardItem::~RewardItem()
{

}

void RewardItem::Update(int deltaTime)
{
	sprite = spriteDrop;
	if (isDrop)
	{
		lifeTime += deltaTime;
		y += vY * deltaTime;
		//sprite = spriteDrop;
		if (lifeTime > 1500)
			this->Remove();
	}
	else
		sprite = NULL;
	if (isGround)
		vY = 0;
	if (sprite == NULL)
		return;
	
	//Xu ly thoi gian ton tai cua RewardItem
	
	sprite->Update(deltaTime);
}

void RewardItem::Collision(list<GameObject*>& obj, int dt)
{
	list<GameObject*>::iterator it;
	for (it = obj.begin(); it != obj.end(); it++)
	{
		GameObject* other = (*it);

		Box box = this->GetBox();
		Box boxOther = other->GetBox();
		Box broadphasebox = getSweptBroadphaseBox(box, dt);

		if (other->id == EnumID::Brick_ID)
		{
			if (AABBCheck(broadphasebox, boxOther))
			{
				ECollisionDirection colDirection;
				float collisionTime = sweptAABB(box, boxOther, colDirection, dt);
				if (collisionTime < 1.0f && collisionTime > 0.0)
				{
					if (colDirection == ECollisionDirection::Colls_Bot)
					{
						isGround = true;
						vY = 0;
						this->y = other->y + this->height;
						return;
					}
				}
			}
		}
	}
}

