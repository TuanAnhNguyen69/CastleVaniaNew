#include "Simon.h"



Simon::Simon():ActiveObject()
{
}

Simon::Simon(int _posX, int _posY, int _width, int _height) : ActiveObject(_posX, _posY, _width, _height, 0, -SPEED_Y, EnumID::Simon_ID)
{
	hp = 40;
	action = Action::Stand;
	g = GRAVITATIONAL;
	isDie = false;
	isJump = false;
	isSit = false;
	isStop = false;
	isAttack = false;

	sprite = new GSprite(TextureManager::getInstance()->getTexture(id), 0, 3, 20);
	simonJum = new GSprite(TextureManager::getInstance()->getTexture(EnumID::Simon_ID), 4, 4, 300);
	simonAttack = new  GSprite(TextureManager::getInstance()->getTexture(EnumID::Simon_ID), 5, 8, 1000/SIMON_FIGHT_RATE);
}

Simon::~Simon()
{
}


void Simon::Draw(GCamera* camera)
{
	//Rot xuong vuc
	if (posY < (camera->viewport.y - G_ScreenHeight))
	{
		hp = 0;
		isDie = true;
	}

	D3DXVECTOR2 center = camera->Transform(posX, posY);
	if (isDie)
	{
		simonDeath->DrawFlipX(center.x, center.y);
	}
	else
	{
		if (vLast > 0)
		{
			if (action == Action::Attack)
			{
				simonAttack->DrawFlipX(center.x, center.y);
				return;
			}
			sprite->DrawFlipX(center.x, center.y);
		}
		else
		{
			if (action == Action::Attack)
			{
				simonAttack->Draw(center.x, center.y);
				return;
			}
			sprite->Draw(center.x, center.y);
		}
			


	}

	

}

void Simon::Update(int deltaTime)
{
	switch (action)
	{
	case Action::Run_Right:
		sprite->Update(deltaTime);
		break;
	case Action::Run_Left:
		sprite->Update(deltaTime);
		break;
	case Action::Attack:
		this->OnAttack(deltaTime);
		break;
	default:
		break;
	}
	//sprite->Update(deltaTime);

	if (isJump)
	{
		sprite->SelectIndex(4);
		posY += vY * deltaTime + 0.4 * deltaTime * deltaTime * g;
		if (vY > SPEED_FALL)
			vY += g * deltaTime;
		return;
	}
	else
		vY = 0;

	posX += vX * deltaTime;

}

void Simon::RunLeft()
{
	if (isStop && vLast < 0)
		vX = 0;
	else 
	{
		isStop = false;
		vX = -SPEED_X;
		vLast = vX;
	}
	action = Action::Run_Left;
}

void Simon::RunRight()
{
	if (isStop && vLast > 0)
		vX = 0;
	else
	{
		isStop = false;
		vX = SPEED_X;
		vLast = vX;
	}
	action = Action::Run_Right;
}

void Simon::Jump()
{
	if (!isJump)
	{
		g = -g;
		vY = sqrt(-2 * g * MAX_HEIGHT);
		sprite->SelectIndex(4);
		action = Action::Jump;
		isJump = true;
	}
	else
		vY = 0;
}

void Simon::Sit()
{
	if (!isJump)
	{
		//posY -= 5;
		sprite->SelectIndex(4);
		vX = 0;
		//vY = -(SPEED_Y + 0.3f);
		vY = 0;
		isSit = true;
		action = Action::Sit;
	}
}

void Simon::Attack()
{
	if (action == Action::Run_Left || action == Action::Run_Right)
		return;
	if (action == Action::Attack)
		return;
	if (!isJump)
		vX = 0;

	action = Action::Attack;
}

void Simon::OnAttack(int deltaTime)
{
	isAttack = true;
	simonAttack->Update(deltaTime);
	if (!isSit && simonAttack->GetIndex() >= 8)
	{
		action = Action::Stand;
		simonAttack->Reset();
	}
}

void Simon::Stop()
{
	vX = 0;
	switch (action)
	{
		case Action::Stand:
		case Action::Attack:
		case Action::Fall:
			return;
	}
	if (isSit)
	{
		posY += 16;
		isSit = false;
	}
	action = Action::Stand;
	sprite->SelectIndex(0);
}

bool Simon::AutoMove(int &rangeMove, int dt)
{
	Stop();
	if (rangeMove == 0)
		return true;
	if (rangeMove > 0)
	{
		rangeMove -= AUTO_MOVE_RANGE;
		posX += AUTO_MOVE_RANGE;
	}
	else
	{
		rangeMove += AUTO_MOVE_RANGE;
		posX -= AUTO_MOVE_RANGE;
	}
	sprite->Update(dt);
	return false;
}

Box Simon::GetBox()
{
	if (isJump || isSit)
	{
		return Box(posX - width / 2 + 14.5f, posY + height / 2 - 3, width - 29, height - 22);
	}
	return Box(posX - width / 2 + 14.5f, posY + height / 2 - 3, width - 29, height - 6);
}

void Simon::StandGround(list<GameObject*> &obj, float dt)
{
	float moveX = 0;
	float moveY = 0;
	float normalx;
	float normaly;
	if (vY < 0 && moveY < 26)
	{


		if (moveY > 0) {
			
			posY += moveY;

			if (isJump)
			{
				isJump = false;
				/*
				if (_hasKnockBack)
				{
					if (!_hidden)
					{
						_hidden = true;
						_startToHiddenTime = GetTickCount();
						if (hp > 0)
						{
							if (hp <= 3)
							{
								hp -= 1;
							}
							else
								hp -= other->damage;
						}

					}
					_hasKnockBack = false;
				}
				*/
				vY = 0;
				vX = 0;
				g = 0;
				//_allowPress = true;
				sprite->SelectIndex(0);
			}

		}
	}
}

void Simon::Collision(list<GameObject*> &obj, float dt)
{
	ActiveObject::Collision(obj, dt);
	StandGround(obj, dt);
}