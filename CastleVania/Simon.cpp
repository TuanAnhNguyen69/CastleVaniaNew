#include "Simon.h"



Simon::Simon():ActiveObject()
{
}

/*
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
*/

Simon::Simon(int _x, int _y) 
	: ActiveObject(_x, _y, 0, -SPEED_Y, EnumID::Simon_ID)
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
	simonAttack = new  GSprite(TextureManager::getInstance()->getTexture(EnumID::Simon_ID), 5, 8, 1000 / SIMON_FIGHT_RATE);
}

Simon::~Simon()
{
}


void Simon::Draw(GCamera* camera)
{
	//Rot xuong vuc
	//if (posY < (camera->viewport.y - G_ScreenHeight))
	if(y - height/2 < (camera->viewport.y - G_ScreenHeight))
	{
		hp = 0;
		isDie = true;
	}

	//D3DXVECTOR2 center = camera->Transform(posX, posY);
	D3DXVECTOR2 pos = camera->Transform(x, y);
	if (isDie)
	{
		//simonDeath->DrawFlipX(center.x, center.y);
		simonDeath->DrawFlipX(pos.x, pos.y);
	}
	else
	{
		if (vLast > 0)
		{
			if (action == Action::Attack)
			{
				//simonAttack->DrawFlipX(center.x, center.y);
				simonAttack->DrawFlipX(pos.x, pos.y);
				return;
			}
			//sprite->DrawFlipX(center.x, center.y);
			sprite->DrawFlipX(pos.x, pos.y);
		}
		else
		{
			if (action == Action::Attack)
			{
				//simonAttack->Draw(center.x, center.y);
				simonAttack->Draw(pos.x, pos.y);
				return;
			}
			//sprite->Draw(center.x, center.y);
			sprite->Draw(pos.x, pos.y);
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

	x += vX * deltaTime;

	if (isJump)
	{
		sprite->SelectIndex(4);
		//posY += vY * deltaTime + 0.4 * deltaTime * deltaTime * g;
		y += vY * deltaTime + 0.4 * deltaTime * deltaTime * g;
		if (vY > SPEED_FALL)
			vY += g * deltaTime;
		return;
	}
	//else
		//y += vY * deltaTime;
	
}

void Simon::RunLeft()
{
	if (isJump || isSit)
		return;
	if (isStop && vLast < 0)
		vX = 0;
	else 
	{
		isStop = false;
		vX = -SPEED_X;
		vLast = vX;
	}
	isSit = false;
	action = Action::Run_Left;
}

void Simon::RunRight()
{
	if (isJump || isSit)
		return;
	if (isStop && vLast > 0)
		vX = 0;
	else
	{
		isStop = false;
		vX = SPEED_X;
		vLast = vX;
	}
	isSit = false;
	action = Action::Run_Right;
}

void Simon::Jump()
{
	if (isSit)
		return;
	if (!isJump)
	{
		g = -g;
		vY = sqrt(-2 * g * MAX_HEIGHT);
		sprite->SelectIndex(4);
		action = Action::Jump;
		isJump = true;
	}
}

void Simon::Sit()
{
	if (isSit)
		return;
	if (!isJump)
	{
		y -= 16;
		sprite->SelectIndex(4);
		vX = 0;
		vY = -(SPEED_Y + 0.3f);
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
		//posY += 16;
		//y += 16;
		isSit = false;
	}
	//if (!isJump)
	//	vX = 0;
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
		x += AUTO_MOVE_RANGE;
	}
	else
	{
		rangeMove += AUTO_MOVE_RANGE;
		y -= AUTO_MOVE_RANGE;
	}
	sprite->Update(dt);
	return false;
}

//Do sprite lon hon co the thuc cua Simon
Box Simon::GetBox()
{
	if (isJump || isSit)
	{
		//return Box(posX - width / 2 + 14.5f, posY + height / 2 - 3, width - 29, height - 22);
		return Box(x + 14.5f, y - 3, width - 29, height - 22);
		//return Box(x , y, width, height);
	}
	//return Box(posX - width / 2 + 14.5f, posY + height / 2 - 3, width - 29, height - 6);
	return Box(x + 14.5f, y - 3, width - 29, height - 6);
	//return Box(x, y , width, height);
}

void Simon::StandGround(GameObject* &obj, float dt)
{
	//float moveX = 0.0f;
	//float moveY = 0.0f;
	float normalx = 0.0f;
	float normaly = 0.0f;
	Box box = this->GetBox();
	Box boxOther = obj->GetBox();

	
	if (AABBCheck(box, boxOther))
		isOnBrick = false;

	Box tempBox = GetSweptBroadphaseBox(box);
	if (AABBCheck(tempBox, boxOther))
	{
		float timeColl = SweptAABB(box, boxOther, normalx, normaly);
		if (timeColl >= 0.0f && timeColl < 1.0f)
		{
			//printf("%f", timeColl);
			
			//y = 200
			if (normaly == 1.0f)
			{
				y += vY * timeColl + 16;
				//y = boxOther.y + box.h;
				//x += vX * timeColl;
				isOnBrick = true;
				vY = 0;
				vX = 0;
				g = 0;
				sprite->SelectIndex(0);
				if (isJump)
					isJump = false;
				x = vX * dt;
				return;
			}
			
		}
	}
	else
		isOnBrick = false;
	

	/*
	if (AABB(box, boxOther, moveX, moveY) == true)
	{

		float collisiontime = SweptAABB(box, boxOther, normalx, normaly, dt);
		//if (normalx == 0 && normaly == -1)
		{
			isOnBrick = true;
			if (vY < 0 && moveY < 26)
			{
				if (moveY > 0)
				{
					//posY += moveY;
					y += moveY + 16;
					if (isJump)
					{
						isJump = false;
					}
					vY = 0;
					vX = 0;
					g = GRAVITATIONAL;
					sprite->SelectIndex(0);
					return;
				}
				x += vX * dt;

			}
		}
	}
	*/
}

void Simon::Collision(list<GameObject*> &obj, float dt)
{
	
	list<GameObject*>::iterator _itBegin;
	for (_itBegin = obj.begin(); _itBegin != obj.end(); _itBegin++)
	{
		//float moveX = 0;
		//float moveY = 0;
		//float normalx = 0;
		//float normaly = 0;
		GameObject* other = (*_itBegin);

		if (other->id == EnumID::Brick_ID)
		{
			StandGround(other, dt);
		}
	}
}