
#include "GameObject.h"
#include <d3d9.h>

GameObject::GameObject(void)
{
	x = 0;
	y = 0;
	width = 0;
	height = 0;
	canMove = false;
	canBeKilled = true;
}

GameObject::GameObject(float _x, float _y, EnumID _id)
{
	x = _x;
	y = _y;
	vX = 0;
	vY = 0;
	id = _id;
	isDrop = false;
	type = ObjectType::None;
	canMove = false;
	active = true;
	//damage = 0;
	CreateSprite();
	if (sprite != NULL)
	{
		width = sprite->_texture->FrameWidth;
		height = sprite->_texture->FrameHeight;
	}
}

GameObject::~GameObject(void) 
{
}


void GameObject::CreateSprite()
{
	switch (id)
	{
	case EnumID::Brick_ID:
	case EnumID::Tele_ID:
		sprite = NULL;
		break;
	case EnumID::MovingPlatform_ID:
		sprite = new GSprite(TextureManager::getInstance()->getTexture(id), 16);
		break;
	case EnumID::Simon_ID:
		sprite = new GSprite(TextureManager::getInstance()->getTexture(id), 0, 3, 100);
		break;
	case EnumID::Candle_ID:
		sprite = new GSprite(TextureManager::getInstance()->getTexture(id), 0, 3, 100);
		break;
	case EnumID::Breakable_ID:
		sprite = new GSprite(TextureManager::getInstance()->getTexture(id), 0, 0, 100);
		break;
	case EnumID::MedusaHead_ID:
		sprite = new GSprite(TextureManager::getInstance()->getTexture(id), 0, 1, 100);
		break;
	case EnumID::Bat_ID:
		sprite = new GSprite(TextureManager::getInstance()->getTexture(id), 0, 3, 100);
		break;
	case EnumID::Door_ID:
		sprite = new GSprite(TextureManager::getInstance()->getTexture(id), 0, 0, 10);
		break;
	case EnumID::SpearGuard_ID:
		sprite = new GSprite(TextureManager::getInstance()->getTexture(id), 0, 3, 10);
		break;
	case EnumID::Skeleton_ID:
		sprite = new GSprite(TextureManager::getInstance()->getTexture(id), 0, 3, 500);
		break;
	case EnumID::BonePillar_ID:
		sprite = new GSprite(TextureManager::getInstance()->getTexture(id), 12);
		break;
	case EnumID::Boomerang_Weapon_ID:
		sprite = new GSprite(TextureManager::getInstance()->getTexture(id), 16);
		break;
	case EnumID::Knife_Weapon_ID:
		sprite = new GSprite(TextureManager::getInstance()->getTexture(id), 16);
		break;
	case EnumID::Axe_Weapon_ID:
		sprite = new GSprite(TextureManager::getInstance()->getTexture(id), 16);
		break;
	case EnumID::HolyWater_Weapon_ID:
		sprite = new GSprite(TextureManager::getInstance()->getTexture(id), 16);
		break;
	case EnumID::Fire_ID:
		sprite = new GSprite(TextureManager::getInstance()->getTexture(id), 16);
		break;
	case EnumID::Medusa_ID:
		sprite = new GSprite(TextureManager::getInstance()->getTexture(id), 0, 4, 100);
		break;
	case EnumID::Snake_ID:
		sprite = new GSprite(TextureManager::getInstance()->getTexture(id), 16);
		break;
	case EnumID::SpiritBall_ID:
		sprite = new GSprite(TextureManager::getInstance()->getTexture(id), 50);
		break;
	case EnumID::Cross_ID:
	case EnumID::BigHeart_ID:
	case EnumID::SmallHeart_ID:
	case EnumID::Axe_ID:
	case EnumID::Boomerang_ID:
	case EnumID::HolyWater_ID:
	case EnumID::PorkChop_ID:
	case EnumID::MoneyBag400_ID:
	case EnumID::MoneyBag700_ID:
	case EnumID::MorningStar_ID:
	case EnumID::DoubleShot_ID:
	case EnumID::TripleShot_ID:
		sprite = new GSprite(TextureManager::getInstance()->getTexture(id), 16);
		break;
	}
}


void GameObject::Update(int dt)
{
	if (sprite != NULL)
		sprite->Update(dt);
}
void GameObject::Update(float _xSimon, float _ySimon, int dt)
{

}
void GameObject::Draw(GCamera* camera)
{
	if (sprite != NULL)
	{
		D3DXVECTOR2 pos = camera->Transform(x, y);
		sprite->Draw(pos.x, pos.y);
	}
}


void GameObject::ReceiveDamage(int _damage)
{
	if (hp > 0)
		hp -= _damage;
	if (hp <= 0)
	{
		isDeath = true;
	}
}

void GameObject::SetActive(float _xSimon, float _ySimon)
{

}

void GameObject::Collision(list<GameObject*> &obj, int dt)
{
}

void GameObject::CollSimon(GameObject* simon, int dt)
{
}

void GameObject::Remove()
{
	active = false;
	isDeath = true;
}


Box GameObject::GetBox()
{
	Box result(x, y, width, height, vX, vY);
	return result;
}

D3DXVECTOR2 GameObject::GetPos()
{
	D3DXVECTOR2 pos(x - width / 2, y - height / 2);
	return pos;
}

/*
void GameObject::Pause() {
	vX = 0;
	vY = 0;
}
*/

ECollisionDirection GameObject::GetCollisionDirect(float normalx, float normaly)
{
	if (normalx == 0 && normaly == 1)
	{
		return ECollisionDirection::Colls_Bot;
	}
	if (normalx == 0 && normaly == -1)
	{
		return ECollisionDirection::Colls_Top;
	}
	if (normalx == 1 && normaly == 0)
	{
		return ECollisionDirection::Colls_Left;
	}
	if (normalx == -1 && normaly == 0)
	{
		return ECollisionDirection::Colls_Right;
	}
	return ECollisionDirection::Colls_None;
}
