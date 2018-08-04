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

	//onStair = false;
	outStair = false;
	//startStair = false;
	upStair = false;
	downStair = false;
	standOnStair = false;
	colStair = false;


	live = 10;
	weaponCount = 10;
	weaponID = EnumID::Boomerang_ID;
	morningStar = new MorningStar(x, y, 20);

	sprite = new GSprite(TextureManager::getInstance()->getTexture(id), 0, 3, 20);
	simonJum = new GSprite(TextureManager::getInstance()->getTexture(EnumID::Simon_ID), 4, 4, 300);
	simonAttack = new  GSprite(TextureManager::getInstance()->getTexture(EnumID::Simon_ID), 5, 8, 20);
	simonUpStair = new GSprite(TextureManager::getInstance()->getTexture(EnumID::Simon_ID), 12, 13, 20);
	simonDownStair = new GSprite(TextureManager::getInstance()->getTexture(EnumID::Simon_ID), 10, 11, 20);

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
 		simonDeath->DrawFlipX(pos.x, pos.y);
	}
	else
	{
		if (vX > 0 || vLast > 0)
		{
			if (action == Action::Attack)
			{
				//simonAttack->DrawFlipX(center.x, center.y);
				simonAttack->DrawFlipX(pos.x, pos.y);
				morningStar->Draw(camera);
				return;
			}

			if (onStair)
			{
				if (vY > 0) {
					simonUpStair->DrawFlipX(pos.x, pos.y);

				}
				else {
					simonDownStair->DrawFlipX(pos.x, pos.y);
				}
				return;
			}
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
			if (onStair)
			{	
				if (vY > 0) {
					simonUpStair->Draw(pos.x, pos.y);

				}
				else {
					simonDownStair->Draw(pos.x, pos.y);
				}
				return;
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
	case Action::UpStair:
		simonUpStair->Update(deltaTime);
		break;
	case Action::DownStair:
		simonDownStair->Update(deltaTime);
		break;
	default:
		break;
	}

	x += vX * deltaTime;

	if (isJump)
	{
		sprite->SelectIndex(4);
		//posY += vY * deltaTime + 0.4 * deltaTime * deltaTime * g;
		y += vY * deltaTime + 0.4 * deltaTime * deltaTime * g;
		if (vY > -SPEED_Y)
			vY += g * deltaTime;
		return;
	} 
		y += vY * deltaTime;
}


void Simon::RunLeft()
{
	morningStar->updateDirection(true);
	isLeft = true;
	if (onStair) {
		if (stair->type == EStairType::BotLeft || stair->type == EStairType::TopLeft) {
			goUpStair();
		}
		else if (stair->type == EStairType::BotRight || stair->type == EStairType::TopRight) {
			goDownStair();
		}
		return;
	}

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
	isLeft = false;
	if (onStair) {
		if (stair->type == EStairType::BotLeft || stair->type == EStairType::TopLeft) {
			goDownStair();
		}
		else if (stair->type == EStairType::BotRight || stair->type == EStairType::TopRight) {
			goUpStair();
		}
		return;
	}
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
	if (onStair) {
		return;
	}
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

void Simon::onMovingOnStair(int deltaTime)
{
	simonUpStair->Update(deltaTime);
}

void Simon::Stop()
{
	vX = 0;
	if (onStair) {
		vY = 0;
	}
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
		return Box(x + 15, y - 22, width - 32, height - 22, vX, vY);
		//return Box(x , y, width, height);
	}
	//return Box(posX - width / 2 + 14.5f, posY + height / 2 - 3, width - 29, height - 6);
	return Box(x + 15, y - 3, width - 32, height - 6, vX, vY);
	//return Box(x, y , width, height);
}

void Simon::onCollideBrick(Box other, int dt, ECollisionDirection colDirection, float collisionTime)
{
	//colStair = false;


			if (colDirection == ECollisionDirection::Colls_Bot)
			{
				this->y = other.y + this->height -2;
				//vY = 0;

				this->vY = 0;
				colStair = false;
				action = Action::Stand;
				onStair = false;
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

void Simon::onCollideStair(Stair * other)
{
	colStair = true;
	stair = other;
}

void Simon::goUpStair()
{
	
	if (action == Action::Stand && !colStair) {
		return;
	}

	float simonX = this->x;
	float startPos = getStairStartPos();
	int offset = abs(simonX - startPos);
	if (offset > 10 && !onStair) {
		if (this->x < getStairStartPos()) {
			RunRight();
			return;
		}
		else if (this->x  > getStairStartPos()) {
			RunLeft();
			return;
		}
	}
	
	onStair = true;
	if (isSit || isJump)
		return;
	if (colStair)
	{
		action = Action::UpStair;
		if (stair->type == EStairType::BotLeft || stair->type == EStairType::TopLeft) {
			vX = -0.2;
		}
		else {
			vX = 0.2;
		}
		vY = 0.2;
	}
}

float Simon::getStairStartPos() {
	if (stair->type == EStairType::BotRight || stair->type == EStairType::TopLeft) {
		return stair->x - stair->width;
	}

	if (stair->type == EStairType::BotLeft || stair->type == EStairType::TopRight) {
		return stair->x + stair->width/2;
	}
}

void Simon::goDownStair()
{
	if (action == Action::Sit && !colStair) {
		return;
	}

	float simonX = this->x;
	float startPos = getStairStartPos();
	int offset = abs(simonX - startPos);
	if (offset > 10 && !onStair) {
		if (this->GetBox().x  < getStairStartPos()) {
			RunRight();
			return;
		}
		else if (this->GetBox().x > getStairStartPos()) {
			RunLeft();
			return;
		}
	}
	onStair = true;

	if (isSit || isJump)
		return;
	if (colStair)
	{
		action = Action::DownStair;
		if (isLeft) {
			vX = -0.2;
		}
		else {
			vX = 0.2;
		}
		vY = -0.2;
	}
}

void Simon::Collision(list<GameObject*> &obj, float dt)
{
	list<GameObject*> listObject;

	list<GameObject*>::iterator _itBegin;
	bool isCollideBottom = false;
	Box fallBox = this->GetBox();
	fallBox.h = fallBox.h + 10;
	for (_itBegin = obj.begin(); _itBegin != obj.end(); _itBegin++)
	{
		GameObject* other = (*_itBegin);
		
		
		Box box = this->GetBox();
		Box boxOther = other->GetBox();
		Box broadphasebox = getSweptBroadphaseBox(box, dt);

		// Check if simon is standing on brick or stair
		if (!isCollideBottom && other->id == EnumID::Brick_ID) {
			isCollideBottom = AABBCheck(fallBox, boxOther);
		}

		if (other->id == EnumID::Brick_ID) {
			if (AABBCheck(broadphasebox, boxOther))
			{
				ECollisionDirection colDirection;
				float collisionTime = sweptAABB(box, boxOther, colDirection, dt);
				if ( collisionTime < 1.0f && collisionTime > 0.0) //collisiontime > 0 &&
				{
					onCollideBrick(boxOther, dt, colDirection, collisionTime);
				}
			}
		}
		else {
			listObject.push_back(*_itBegin);
		}
	}

	for (_itBegin = listObject.begin(); _itBegin != listObject.end(); _itBegin++)
	{
		GameObject* other = (*_itBegin);
		Box box = this->GetBox();
		Box boxOther = other->GetBox();
		Box broadphasebox = getSweptBroadphaseBox(box, dt);

		// Check if simon is standing on brick or stair
		if (!isCollideBottom && (other->id == EnumID::StairTopLeft_ID || other->id == EnumID::StairTopRight_ID || other->id == EnumID::StairRight_ID || other->id == EnumID::StairLeft_ID)) {
			isCollideBottom = AABBCheck(fallBox, boxOther);

			//If stand on top stair
			if (other->id == EnumID::StairTopLeft_ID || other->id == EnumID::StairTopRight_ID && !onStair) {
				onCollideStair((Stair*)other);
			}
		}

		if (AABBCheck(broadphasebox, boxOther))
		{
			ECollisionDirection colDirection;
			float collisionTime = sweptAABB(box, boxOther, colDirection, dt);
			if (collisionTime < 1.0f && collisionTime > 0.0) //collisiontime > 0 &&
			{
				switch (other->id)
				{
				case EnumID::StairBotLeft_ID:
				case EnumID::StairBotRight_ID:
				case EnumID::StairTopLeft_ID:
				case EnumID::StairTopRight_ID:
					onCollideStair((Stair*)other);
					break;
				case EnumID::SpearGuard_ID:
					this->ReceiveDamage(other);
					sprite->SelectIndex(8);
					break;
				default:
					break;
				}
			}
		}

	}

	if (!isCollideBottom && !isJump && !onStair) {
		fall();
	}

}

void Simon::Die()
{

}

void Simon::fall()
{
	vY = -SPEED_Y;
}



void Simon::ReceiveDamage(GameObject *enemy)
{
	hp -= enemy->damage;
}