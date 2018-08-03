#include "Simon.h"



Simon::Simon():ActiveObject()
{
}

Simon::Simon(int _x, int _y) 
	: ActiveObject(_x, _y, 0, -SPEED_Y, EnumID::Simon_ID)
{
	hp = 10;
	action = Action::Stand;
	score = 10;
	g = GRAVITATIONAL;
	isDie = false;
	isJump = false;
	isSit = false;
	isStop = false;
	isAttack = false;
	isOnBrick = false;
	isLeft = true;

	live = 10;
	weaponCount = 10;
	weaponID = EnumID::Boomerang_ID;
	morningStar = new MorningStar(x, y, 20);

	sprite = new GSprite(TextureManager::getInstance()->getTexture(id), 0, 3, 20);
	simonJum = new GSprite(TextureManager::getInstance()->getTexture(EnumID::Simon_ID), 4, 4, 300);
	simonAttack = new  GSprite(TextureManager::getInstance()->getTexture(EnumID::Simon_ID), 5, 8, 20);
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
				morningStar->Draw(camera);

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
				morningStar->Draw(camera);
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
	//vY = -(SPEED_Y + 0.3f);
	//y += vY * deltaTime;
	if (isJump)
	{
		sprite->SelectIndex(4);
		//posY += vY * deltaTime + 0.4 * deltaTime * deltaTime * g;
		y += vY * deltaTime + 0.4 * deltaTime * deltaTime * g;
		if (vY > -SPEED_Y)
			vY += g * deltaTime;
		return;
	}
	else {
		y += vY * deltaTime;
	}
}


void Simon::RunLeft()
{
	morningStar->updateDirection(true);
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
	morningStar->updateDirection(false);

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
	if (isSit || isJump)
		return;
	if (!isJump)
	{
		g = -GRAVITATIONAL;
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
		sprite->SelectIndex(4);
		vX = 0;
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
	morningStar->update(x, y, deltaTime);
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
		return Box(x + 12, y - 22, width - 29, height - 22, vX, vY);
		//return Box(x , y, width, height);
	}
	//return Box(posX - width / 2 + 14.5f, posY + height / 2 - 3, width - 29, height - 6);
	return Box(x + 12, y - 3, width - 29, height - 6, vX, vY);
	//return Box(x, y , width, height);
}

void Simon::StandGround(ECollisionDirection colDirection, float dt)
{
	if (colDirection == ECollisionDirection::Colls_Bot) {
		this->vY = 0;
		isOnBrick = true;
	}
	else
		isOnBrick = false;
	

	if (colDirection == ECollisionDirection::Colls_Left || colDirection == ECollisionDirection::Colls_Right) {
		this->vX = 0;
	}
	action = Action::Stand;
	isJump = false;
	g = GRAVITATIONAL;
	sprite->SelectIndex(0);
}

void Simon::StandBrick(Box other, int dt, ECollisionDirection colDirection, float collisionTime)
{
			if (colDirection == ECollisionDirection::Colls_Bot)
			{
				this->y = other.y + this->height;
				//vY = 0;

				this->vY = 0;

				action = Action::Stand;
				isJump = false;
				g = GRAVITATIONAL;
				sprite->SelectIndex(0);
				return;
			}

			if (colDirection == ECollisionDirection::Colls_Left)
			{
				this->x += this->vX * collisionTime * dt + 5;
				action = Action::Stand;
				return;
			}

			if (colDirection == ECollisionDirection::Colls_Right)
			{
				this->x += this->vX * collisionTime * dt - 5;
				action = Action::Stand;
				return;
			}
}

void Simon::Collision(list<GameObject*> &obj, float dt)
{
	
	list<GameObject*>::iterator _itBegin;
	for (_itBegin = obj.begin(); _itBegin != obj.end(); _itBegin++)
	{
		GameObject* other = (*_itBegin);
		
		Box box = this->GetBox();
		Box boxOther = other->GetBox();
		Box broadphasebox = getSweptBroadphaseBox(box, dt);
		if (box.x + box.w >= 3865 && boxOther.x > 3865) {
			int a = 0;
		}
		if (AABBCheck(broadphasebox, boxOther))
		{
			ECollisionDirection colDirection;
			float collisionTime = sweptAABB(box, boxOther, colDirection, dt);
			if ( collisionTime < 1.0f && collisionTime > 0.0) //collisiontime > 0 &&
			{
				if (other->id == EnumID::Brick_ID)
				{
					StandBrick(boxOther, dt, colDirection, collisionTime);
				}
				
			}
		}
		
	}
}