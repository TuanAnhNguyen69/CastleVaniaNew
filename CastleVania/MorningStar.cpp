#include "MorningStar.h"

MorningStar::MorningStar(void) :GameObject()
{
	
}

MorningStar::MorningStar(int posX, int posY, int timeAnimation) : GameObject(posX, posY, id)
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
	D3DXVECTOR2 pos = camera->Transform(x, y);
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
		width = 16;
		height = 48;
		break;
	default:
		width = 42;
		height = 16;
		break;
	}
	return Box(x, y, width, height);
}

void MorningStar::update(int _posX, int _posY, int deltaTime)
{
	sprite->Update(deltaTime);
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
			morningStarX = _posX - 90 + 20;
			morningStarY = _posY;
			break;
		case 1:
			morningStarX = _posX - 105 + 20;
			morningStarY = _posY;
			break;
		case 2:
			morningStarX = _posX + 32 - 145 + 20;
			morningStarY = _posY;
			break;
		default:
			int i = 0;
			break;
		}
	} else 	{
		switch (morningState % 3)
		{
		case 0:
			morningStarX = _posX + 32 - 150; // 40
			morningStarY = _posY;
			break;
		case 1:
			morningStarX = _posX + 32 - 135; // 30
			morningStarY = _posY;
			break;
		case 2:
			morningStarX = _posX - 95; //5
			morningStarY = _posY;
			break;
		default:
			break;
		}
	}
	this->x = morningStarX;
	this->y = morningStarY;
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

void MorningStar::Collision(list<GameObject*> &obj, int dt){
	list<GameObject*>::reverse_iterator _itBegin;
	for (_itBegin = obj.rbegin(); _itBegin != obj.rend(); _itBegin++)
	{
		GameObject* other = (*_itBegin);

			Box box = this->GetBox();
			Box boxOther = other->GetBox();


			// edit AABB later
			if (AABBCheck(box, boxOther) == true)
			{
					if ( other->canBeKilled )
					{
						/*if (other->id == EnumID::Medusa_ID)
						{
							Medusa* qm = (Medusa*)other;
							if (qm->HasGetUp)
							{
								other->ReceiveDamage(damage);
								if (other->hp <= 0)
								{
									point += other->point;
								}
							}
							else
								qm->getUp();
						}*/
						/*else*/
						if (other->id == EnumID::Breakable_ID) {
							point += other->point;
						}
						else
						{
							//other->ReceiveDamage(damage);
							//if (other->hp <= 0)
							{
								point += other->point;
							}
							
						}
						
					}
				return;
			}
		}
}

MorningStar::~MorningStar(void)
{
}
