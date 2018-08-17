#include "MorningStar.h"

MorningStar::MorningStar(void) :GameObject()
{
	
}

MorningStar::MorningStar(float _x, float _y, int timeAnimation) : GameObject(_x, _y, EnumID::MorningStar_Weapon_ID)
{
	isLeft = true;
	damage = 1;
	level = 1;
	damage = 1;
	lv1 = new GSprite(TextureManager::getInstance()->getTexture(EnumID::MorningStar_Weapon_ID), 0, 2, timeAnimation);
	lv2 = new GSprite(TextureManager::getInstance()->getTexture(EnumID::MorningStar_Weapon_ID), 3, 5, timeAnimation);
	lv3 = new GSprite(TextureManager::getInstance()->getTexture(EnumID::MorningStar_Weapon_ID), 6, 14, timeAnimation / 3);
	sprite = lv1;
}

void MorningStar::resetLevel()
{
	level = 1;
	damage = 1;
}

void MorningStar::resetSprite()
{
	sprite->Reset();
}


void MorningStar::Draw(GCamera* camera)
{
	D3DXVECTOR2 pos = camera->Transform(drawX, drawY);
	if (!isLeft)
	{
		sprite->DrawFlipX(pos.x, pos.y);
	}
	else
	{
		sprite->Draw(pos.x, pos.y);
	}
}

void MorningStar::updateDirection(bool isLeft) {
	this->isLeft = isLeft;
}

Box MorningStar::GetBox()
{
	int currentState = sprite->GetIndex();
	if (currentState < 0 || currentState > 8)
		return Box(0, 0, 0, 0);
	float width, height;
	int morningState = this->sprite->GetIndex();
	int posX, posY;
	int lv3Length = 0;
	if (level == 3) {
		if (morningState <= 8) {
			morningState = 0;
		}
		else if (morningState >= 12) {
			morningState = 2;
		}
		else {
			morningState = 1;
		}
		lv3Length = 5;
	}

	posX = x;
	switch (morningState % 3)
	{
	case 0:
		width = 16;
		height = 48;
		break;
	case 1:
		width = 32;
		height = 40;
		break;
	case 2:
		width = 42 + lv3Length;
		height = 16;
		if (!isLeft) {
			posX = x + 32;
		}
		else {
			posX = x - width;
		}
		break;
	default:
		break;
	}
	return Box(posX, y, width, height);
}

void MorningStar::update(int _posX, int _posY, int deltaTime)
{
	sprite->Update(deltaTime);
	this->x = _posX;
	this->y = _posY;
	float morningStarX = 0;
	float morningStarY = 0;
	int morningState = this->sprite->GetIndex();
	if (level == 3) {
		if (morningState <= 8) {
			morningState = 0;
		}
		else if (morningState >= 12) {
			morningState = 2;
		}
		else {
			morningState = 1;
		}
	}

	if (!isLeft) {
		switch (morningState % 3)
		{
		case 0:
			morningStarX = _posX - 90 + 20 - 16;
			morningStarY = _posY;
			break;
		case 1:
			morningStarX = _posX - 105 + 20 - 16;
			morningStarY = _posY;
			break;
		case 2:
			morningStarX = _posX + 32 - 145 + 20 - 16;
			morningStarY = _posY;
			break;
		default:
			int i = 0;
			break;
		}
	}
	else {
		switch (morningState % 3)
		{
		case 0:
			morningStarX = _posX + 32 - 150 - 8; // 40
			morningStarY = _posY;
			break;
		case 1:
			morningStarX = _posX + 32 - 135 - 8; // 30
			morningStarY = _posY;
			break;
		case 2:
			morningStarX = _posX - 95 - 8; //5
			morningStarY = _posY;
			break;
		default:
			break;
		}
	}
	this->drawX = morningStarX;
	this->drawY = morningStarY;
}

void MorningStar::UpdateLevel()
{
	if (level == 3) {
		return;
	}

	this->level++;

	switch (level)
	{
	case 1:
		sprite = lv1;
		break;
	case 2:
		sprite = lv2;

		break;
	case 3:
		sprite = lv3;
		break;
	default:
		break;
	}
}

void MorningStar::Collision(list<GameObject*> &obj, int dt)
{
	list<GameObject*>::reverse_iterator _itBegin;
	for (_itBegin = obj.rbegin(); _itBegin != obj.rend(); _itBegin++)
	{
		GameObject* other = (*_itBegin);
		if (other->active) {
			Box box = this->GetBox();
			Box boxOther = other->GetBox();

			box.vx -= boxOther.vx;
			box.vy -= boxOther.vy;

			Box broadphasebox = getSweptBroadphaseBox(box, dt);

			if (other->id == SpearGuard_ID) {
				int a = 0;
			}

			// edit AABB later
			if (AABBCheck(box, boxOther))
			{
				//if (other->canBeKilled)
				{
					if (other->type == ObjectType::Enemy_Type)
					{
						if (other->id == EnumID::Medusa_ID)
						{
							MedusaBoss* ms = (MedusaBoss*)other;
							if (ms->getUp)
							{
								other->ReceiveDamage(this->damage);
								if (other->hp <= 0)
								{
									point += other->point;
								}
								sound->PlayEffectSound(EEffectSound::EHitSound);
							}
							else {
								ms->getUp = true;
							}
						}
						else
						{
							other->ReceiveDamage(this->damage);
							if (other->hp <= 0)
							{
								point += other->point;
								//other->active = false;
							}
							sound->PlayEffectSound(EEffectSound::EHitSound);
						}
					}
					if (other->id == Candle_ID)
					{
						other->Remove();
						sound->PlayEffectSound(EEffectSound::EHitSound);
					}
					return;
				}
				if (other->type == ObjectType::Item)
				{
					other->isDrop = true;
					//return;
				}
				
			}
		}
	}
}

MorningStar::~MorningStar(void)
{
}
