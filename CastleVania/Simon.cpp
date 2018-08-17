#include "Simon.h"



Simon::Simon():Enemy()
{
}

Simon::Simon(int _x, int _y) 
	: Enemy(_x, _y, 0, -SPEED_Y, EnumID::Simon_ID)
{
	hp = 20;
	action = Action::SimonStand;
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
	standOnStair = false;
	colStair = false;
	onTopStair = false;
	isOnMovingPlatform = false;
	immuteTime = 0;

	//isOnMovingPlatform = false;
	isPickUpSpiritBall = false;
	canPress = true;
	timeOnStair = 0;
	knockBackTime = 0;
	type = ObjectType::None;

	sub_weapon = new list<Weapon*>();
	live = 10;
	weaponCount = 10;
	weaponID = EnumID::HolyWater_Weapon_ID;
	morningStar = new MorningStar(x, y, 42);

	isUseCross = false;

	doorDirection = NoneDoor;

	simonMove = new GSprite(TextureManager::getInstance()->getTexture(id), 0, 2, 20);
	simonJump = new GSprite(TextureManager::getInstance()->getTexture(EnumID::Simon_ID), 4, 4, 300);
	simonAttack = new GSprite(TextureManager::getInstance()->getTexture(EnumID::Simon_ID), 5, 7, 42);
	simonAttackUpStair = new GSprite(TextureManager::getInstance()->getTexture(EnumID::Simon_ID), 21, 23, 42);		
	simonAttackDownStair = new GSprite(TextureManager::getInstance()->getTexture(EnumID::Simon_ID),18, 20, 42);
	simonSitAttack = new GSprite(TextureManager::getInstance()->getTexture(EnumID::Simon_ID), 15, 17, 42);
	simonUpStair = new GSprite(TextureManager::getInstance()->getTexture(EnumID::Simon_ID), 12, 13, 20);
	simonDownStair = new GSprite(TextureManager::getInstance()->getTexture(EnumID::Simon_ID), 10, 11, 20);
	simonDeath = new GSprite(TextureManager::getInstance()->getTexture(EnumID::SimonDeath_ID), 0, 0, 1);
	simonKnockedBack = new GSprite(TextureManager::getInstance()->getTexture(EnumID::Simon_ID), 8, 8, 1);
	simonSit = new GSprite(TextureManager::getInstance()->getTexture(EnumID::Simon_ID), 4, 4, 300);
}

Simon::~Simon()
{
}

void Simon::UpGradeMorningStar() {
	this->morningStar->UpdateLevel();
}
void Simon::Draw(GCamera* camera)
{
	for (list<Weapon*>::iterator wp = sub_weapon->begin(); wp != sub_weapon->end(); wp++)
	{
		if ((*wp)->active)
			(*wp)->Draw(camera);
	}

	//Rot xuong vuc
	if(y - height < (camera->viewport.y - G_ScreenHeight))
	{
		hp = 0;
		action = Action::SimonDead;
	}

	D3DXVECTOR2 pos = camera->Transform(x, y);

	switch (action)
	{
	case SimonStand:
		if (isOnBrick || onTopStair) {
			simonMove->SelectIndex(0);
			sprite = simonMove;
		}
		else if (upStair) {
			simonUpStair->SelectIndex(12);
			sprite = simonUpStair;
		}
		else {
			simonDownStair->SelectIndex(10);
			sprite = simonDownStair;
		}
		break;
	case SimonRunRight:
	case SimonRunLeft:

		break;
	case SimonJump:
		sprite = simonJump;
		break;
	case SimonUseWeapon:
		if (isSit) {
			sprite = simonSitAttack;
		}
		else if (onStair) {
			if (upStair) {
				sprite = simonAttackUpStair;
			}
			else if (!upStair) {
				sprite = simonAttackDownStair;
			}
		}
		else {
			sprite = simonAttack;
		}
		break;

	case SimonAttack:
		if (isSit) {
			sprite = simonSitAttack;
		}
		else if (onStair) {
			if (upStair) {
				sprite = simonAttackUpStair;
			}
			else if (!upStair) {
				sprite = simonAttackDownStair;
			}
		}
		else {
			sprite = simonAttack;
		}

		morningStar->Draw(camera);
		break;
	case SimonSit:
		sprite = simonSit;
		break;
	case SimonFall:
		break;
	case SimonUpStair:
		sprite = simonUpStair;
		break;
	case SimonDownStair:
		sprite = simonDownStair;
		break;
	case SimonDead:
		sprite = simonDeath;
		break;
	case SimonHit:
		sprite = simonKnockedBack;
		if (isLeft) {
			sprite->DrawFlipX(pos.x, pos.y);
		}
		else {
			sprite->Draw(pos.x, pos.y);
		}
		return;
		break;
	default:
		break;
	}

	if (isDeath)
		simonDeath->Draw(pos.x, pos.y);

	if (!isLeft) {
		sprite->DrawFlipX(pos.x, pos.y);
	}
	else {
		sprite->Draw(pos.x, pos.y);
	}
}

void Simon::Update(int deltaTime)
{
	list<Weapon*>::iterator wp = sub_weapon->begin();
	while (wp != sub_weapon->end())
	{
		if (!(*wp)->active)
		{
			sub_weapon->erase(wp++);
		}
		else
		{
			(*wp)->Update(deltaTime);
			wp++;
		}
	}

	if (immuteTime > 0) {
		immuteTime--;
	}
	switch (action)
	{
	case Action::SimonUseWeapon:
		OnUseWeapon(deltaTime);
		sprite->Update(deltaTime);
		break;
	case Action::SimonAttack:
		this->OnAttack(deltaTime);
		break;
	case Action::SimonUpStair:
		UpdateOnStair(deltaTime);
		return;
		break;
	case Action::SimonDownStair:
		UpdateOnStair(deltaTime);
		return;
		break;
	default:
		sprite->Update(deltaTime);
		break;
	}

	if (isJump)
	{
		x += vX * deltaTime;
		y += vY * deltaTime;
		if (vY > -SPEED_Y)
			vY += -0.5 - g * vY;
		return;
	} 

	if (isKnockedBack) {
		x += vX * deltaTime;
		y += vY * deltaTime;
		if (vY > -SPEED_Y)
			vY += g * deltaTime * 2;
		return;
	}

	x += vX * deltaTime;
	y += vY * deltaTime;
}

void Simon::UpdateOnStair(int t)
{
 	if (onStair && !standOnStair)
	{
		int yDirection = -1;
		int xDirection = 1;
		if (upStair) {
			yDirection = 1;
		}

		if (isLeft) {
			xDirection = -1;
		}

		timeOnStair += 1;
		if (timeOnStair <= 5)
		{
			x += 3.2 * xDirection;
			y += 3.2 * yDirection;
			if (timeOnStair > 1 && timeOnStair < 4) {
				if (upStair) {
					simonUpStair->SelectIndex(13);
				}
				else {
					simonDownStair->SelectIndex(11);
				}
			} else {
				if (upStair) {
					simonUpStair->SelectIndex(12);
				}
				else {
					simonDownStair->SelectIndex(10);
				}
			}
			if (timeOnStair == 5)
			{
				if (onTopStair && upStair) {
					action = Action::SimonStand;
					onStair = false;
					standOnStair = false;
 					upStair = false;
					colStair = false;
					isOnBrick = true;
				}

				if (!onTopStair && !upStair) {
					vY = 0;
				}
				standOnStair = true;
				timeOnStair = 0;
				return;
			}
		}
	}
}


void Simon::RunLeft()
{
	if (action == Action::SimonAttack || !canPress) {
		return;
	}
	morningStar->updateDirection(true);
	isLeft = true;
	if (onStair) {
		if (stair->stairType == EStairType::BotLeft || stair->stairType == EStairType::TopLeft) {
			goUpStair();
		}
		else if (stair->stairType == EStairType::BotRight || stair->stairType == EStairType::TopRight) {
			goDownStair();
		}
		return;
	}

	if (isJump || isSit)
		return;
	if (isStop && isLeft)
		vX = 0;
	else 
	{
		isStop = false;
		vX = -SPEED_X;
		vLast = vX;
	}
	isSit = false;
	action = Action::SimonRunLeft;
}

void Simon::RunRight()
{
	if (action == Action::SimonAttack || !canPress) {
		return;
	}
	morningStar->updateDirection(false);
	isLeft = false;
	if (onStair) {
		if (stair->stairType == EStairType::BotLeft || stair->stairType == EStairType::TopLeft) {
			goDownStair();
		}
		else if (stair->stairType == EStairType::BotRight || stair->stairType == EStairType::TopRight) {
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
	action = Action::SimonRunRight;
}

void Simon::Jump()
{
 	if (isSit || !canPress || onStair || isAttack)
		return;
	if (!isJump)
	{
		g = -GRAVITATIONAL;
		vY = sqrt(-3 * g * MAX_HEIGHT);
		action = Action::SimonJump;
		isJump = true;
	}
}

void Simon::Sit()
{
	if (onStair || onTopStair || !canPress || isAttack) {
		goDownStair();
		return;
	}
	if (isSit)
		return;
	if (!isJump)
	{
		vX = 0;
		isSit = true;
		isOnMovingPlatform = false;
		action = Action::SimonSit;
	}
}

void Simon::Attack()
{
	if (action == Action::SimonAttack || !canPress)
		return;
	if (!isJump)
		vX = 0;
	action = Action::SimonAttack;
	//Sound::GetInstance()->PlayEffectSound(EEffectSound::EMorningStarSound);
	Sound::GetInstance()->PlayEffectSound(EEffectSound::EMorningStarSound);
}

void Simon::OnAttack(int deltaTime)
{
	if (isKnockedBack) {
		return;
	}

	if (isSit && simonSitAttack->GetIndex() >= 17)
	{
		action = Action::SimonSit;
		isAttack = false;
		sprite->Reset();
		morningStar->resetSprite();
		return;
	}
	else if ((onStair && upStair && simonAttackUpStair->GetIndex() >= 23)
		|| (onStair && !upStair && simonAttackDownStair->GetIndex() >= 20)
		|| (isJump && simonAttack->GetIndex() >= 7)
		|| (simonAttack->GetIndex() >= 7)) {

		action = Action::SimonStand;
		isAttack = false;
		sprite->Reset();
		morningStar->resetSprite();
		return;
	}
	isAttack = true;
	sprite->Update(deltaTime);
	Box box = this->GetBox();
	morningStar->update(box.x, box.y, deltaTime);
}

void Simon::OnUseWeapon(int dt)
{
	if (isSit && simonSitAttack->GetIndex() >= 17)
	{
		action = Action::SimonSit;
		sprite->Reset();
		morningStar->resetSprite();
	}
	else if ((onStair && upStair && simonAttackUpStair->GetIndex() >= 23)
		|| (onStair && !upStair && simonAttackDownStair->GetIndex() >= 20)
		|| (!isSit && simonAttack->GetIndex() >= 7)) {
		action = Action::SimonStand;
		sprite->Reset();
		morningStar->resetSprite();
	}
	isAttack = true;
	sprite->Update(dt);
	Box box = this->GetBox();
}

void Simon::Stop()
{
	vX = 0;
	if (isOnMovingPlatform && movingPlatform != NULL) {
		vX += movingPlatform->vX;
	}
	switch (action)
	{
		case Action::SimonStand:
		case Action::SimonAttack:
		case Action::SimonUseWeapon:
		case Action::SimonFall:
		case Action::SimonJump:
			return;
		case Action::SimonHit:
			if (isLeft) {
				vX = SPEED_X;
			}
			else {
				vX = -SPEED_X;
			}
			return;
	}

	if (onStair) {
		vY = 0;
		return;
	}

	if (isSit)
	{
		//y += 16;
		//y += 16;
		isSit = false;
	}
	
	action = Action::SimonStand;
}

bool Simon::AutoMove(int &rangeMove, int dt)
{
	action = SimonRunLeft;
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
		x -= AUTO_MOVE_RANGE;
	}
	sprite->Update(dt);
	return false;
}

void Simon::onCollideDoor(Door * obj, ECollisionDirection direction, float collisionTime, int dt)
{
	
	door = obj;
	door->animating = true;
	

	if (obj->id == EnumID::Tele_ID) {
		if (direction == ECollisionDirection::Colls_Top) {
			doorDirection = TeleUp;
		}
		else {
			doorDirection = TeleDown;

		}
		return;
	}

	if (obj->id == EnumID::Door_ID) {
		if (direction == ECollisionDirection::Colls_Left) {
			doorDirection = DoorLeft;
		}
		else {
			doorDirection = DoorRight;
		}
		return;
	}

}

//Do sprite lon hon co the thuc cua Simon
Box Simon::GetBox()
{
	if (isJump || isSit || isKnockedBack)
	{
		//return Box(x - width / 2 + 14.5f, y + height / 2 - 3, width - 29, height - 22);
		return Box(x + 16, y - 19, width - 32, height - 22, vX, vY);
		//return Box(x , y, width, height);
	}
	//return Box(x - width / 2 + 14.5f, y + height / 2 - 3, width - 29, height - 6);
	return Box(x + 16, y - 3, width - 32, height - 6, vX, vY);
	//return Box(x, y , width, height);
}

EDoorDirection Simon::GetDirectDoor()
{
	return doorDirection;
}

void Simon::onCollideBrick(Box other, int dt, ECollisionDirection colDirection, float collisionTime)
{	
	if (colDirection == ECollisionDirection::Colls_Bot) 
	{
		this->y = other.y + this->height -2;
		//vY = 0;
		/*if (!colStair) {
			stair = NULL;
		}*/
		this->vY = 0;
		action = Action::SimonStand;
		movingPlatform = NULL;
		isOnBrick = true;
		upStair = false;
		onStair = false;
		timeOnStair = 0;
		isOnMovingPlatform = false;
		isKnockedBack = false;
		canPress = true;
		isJump = false;
		g = GRAVITATIONAL;
		return;
	}

	if (colDirection == ECollisionDirection::Colls_Left && !onStair)
	{
		if (isJump || isOnMovingPlatform) {
			vY = 0;
			action = Action::SimonStand;
		}
		this->x += this->vX * collisionTime * dt + 7;
		this->vX = 0;
		action = Action::SimonRunLeft;
		return;
	}

	if (colDirection == ECollisionDirection::Colls_Right && !onStair)
	{
		if (isJump || isOnMovingPlatform) {
			vY = 0;
			action = Action::SimonStand;
		}
		this->x += this->vX * collisionTime * dt - 7;
		this->vX = 0;
		action = Action::SimonRunRight;
		return;
	}
}

void Simon::onCollideStair(Stair * other)
{
	if (isJump) {
		return;
	}
	colStair = true;
	stair = other;
	onTopStair = false;
	//if (other->id == EnumID::StairBotLeft_ID || other->id == EnumID::StairBotRight_ID) {
	//	colBottomStair = true;
	//}
}

void Simon::goUpStair()
{
	if (isSit || isJump || onTopStair || !canPress)
		return;
	if (action == Action::SimonAttack) {
		return;
	}

	/*if (onTopStair && !isOnBrick) {
		action = Action::Stand;
		onStair = false;
		upStair = false;
		isOnBrick = true;
		vY = 0;
		return;
	}*/

	if (isOnBrick && !colStair) {
		return;
	}

	float simonX = this->GetBox().x;
	float startPos = getStairStartPos();
	int offset = abs(simonX - startPos);
	if (offset > 2 && !onStair) {
		if (this->GetBox().x < getStairStartPos()) {
			RunRight();
			return;
		}
		else if (this->GetBox().x > getStairStartPos()) {
			RunLeft();
			return;
		}
	}


	onStair = true;
	isOnBrick = false;
	upStair = true;
	standOnStair = false;
	action = Action::SimonUpStair;

	if (stair->stairType == EStairType::BotLeft || stair->stairType == EStairType::TopLeft) {
		isLeft = true;
		vX = -0.2;
	}
	else {
		isLeft = false;
		vX = 0.2;
	}
	vY = 0.2;
	morningStar->updateDirection(isLeft);
}

float Simon::getStairStartPos() {

	switch (stair->stairType)
	{
	case EStairType::BotRight:
		return stair->x - stair->width / 2; 

	case EStairType::BotLeft:
		return stair->x + stair->width / 2;
	case EStairType::TopRight:
		return stair->x + stair->width / 4 * 3;
	case EStairType::TopLeft:
		return stair->x + stair->width / 4;
	default:
		break;
	}
}


void Simon::OnColideMovingPlatform(MovingPlatform* _boxOther, int dt, ECollisionDirection _colDirection, int _collTime, bool _isMove)
{

	if (_colDirection == ECollisionDirection::Colls_Bot)
	{
 		movingPlatform = _boxOther;
		this->vY = 0;
		this->y = _boxOther->y + this->height - 2;
		isKnockedBack = false;
		isOnMovingPlatform = true;
		canPress = true;
		isJump = false;
		action = Action::SimonStand;
		//isOnMovingPlatform = true;
		g = GRAVITATIONAL;
		this->vX = _boxOther->vX;
		return;
	}
}

void Simon::KnockBack()
{
	if (isKnockedBack || !canPress) {
		return;
	}

	if (isAttack) {
		morningStar->resetSprite();
		isAttack = false;
	}

	if (isLeft) {
		vX = SPEED_X;
	}
	else {
		vX = -SPEED_X;
	}
	g = -GRAVITATIONAL;
	vY = sqrt(-2 * g * MAX_HEIGHT_KNOCKBACK);
	action = Action::SimonHit;
	immuteTime = 30;
	isKnockedBack = true;
}

void Simon::goDownStair()
{
	if (action == Action::SimonAttack || !canPress) {
		return;
	}

	if (isJump)
		return;

	if (isOnBrick && !colStair && (stair->stairType != EStairType::BotLeft || stair->stairType != EStairType::BotRight)) {
		return;
	}

	float simonX = this->GetBox().x;
	float startPos = getStairStartPos();
	int offset = abs(simonX - startPos);
	/*if (offset > 16 && !onStair) {
		if (this->GetBox().x < getStairStartPos()) {
			vY = 0;
			RunRight();
			return;
		}
		else if (this->GetBox().x > getStairStartPos()) {
			vY = 0;
			RunLeft();
			return;
		}
	}*/

	onStair = true;
	isOnBrick = false;
	upStair = false;
	standOnStair = false;
	action = Action::SimonDownStair;

	if (stair->stairType == EStairType::BotLeft || stair->stairType == EStairType::TopLeft || stair->stairType == EStairType::Left) {
		isLeft = false;
		vX = 0.2;
	}
	else {
		isLeft = true;
		vX = -0.2;
	}
	vY = - 0.2;
	morningStar->updateDirection(isLeft);

}

void Simon::Collision(list<GameObject*> &obj, float dt)
{
	list<GameObject*>::iterator _itBegin;

#pragma region Va chạm với Brick
	list<GameObject*> listObject;
	colStair = false;
	onTopStair = false;
	
	bool isCollideBottom = false;
	Box fallBox = this->GetBox();
	fallBox.h = fallBox.h + 10;

	for (_itBegin = obj.begin(); _itBegin != obj.end(); _itBegin++)
	{
		GameObject* other = (*_itBegin);
		if (other->active) {
			Box box = this->GetBox();
			Box boxOther = other->GetBox();
			Box broadphasebox = getSweptBroadphaseBox(box, dt);

			// Check if simon is standing on brick
			if (!isCollideBottom && other->id == EnumID::Brick_ID) {
				isCollideBottom = AABBCheck(fallBox, boxOther);
			}

			if (other->id == EnumID::Brick_ID)
			{
				if (AABBCheck(broadphasebox, boxOther))
				{
					ECollisionDirection colDirection;
					float collisionTime = sweptAABB(box, boxOther, colDirection, dt);
					if (collisionTime < 1.0f && collisionTime > 0.0) //collisiontime > 0 &&
					{
						onCollideBrick(boxOther, dt, colDirection, collisionTime);
					}
				}
			}
			else {
				listObject.push_back(*_itBegin);
			}
		}
	}

	if (action == SimonAttack) {
		morningStar->Collision(listObject, dt);
	}

	list<Weapon*>::iterator _wb;

	for (_wb = sub_weapon->begin(); _wb != sub_weapon->end(); _wb++)
	{
		(*_wb)->Collision(obj, dt);

		if ((*_wb)->id == EnumID::Boomerang_Weapon_ID)
			(*_wb)->CollSimon(this, dt);
	}

#pragma region Va chạm với Moving Platform

	bool isOnMovingPlatform = false;

	for (_itBegin = listObject.begin(); _itBegin != listObject.end(); _itBegin++)
	{
		GameObject* other = (*_itBegin);

		Box box = this->GetBox();
		Box boxOther = other->GetBox();
		box.vx -= boxOther.vx;
		box.vy -= boxOther.vy;
		Box broadphasebox = getSweptBroadphaseBox(box, dt);

		if (!isOnMovingPlatform && other->id == EnumID::MovingPlatform_ID) {
			isOnMovingPlatform = AABBCheck(fallBox, boxOther);
		}

		if (other->id == EnumID::MovingPlatform_ID)
		{
			if (AABBCheck(broadphasebox, boxOther))
			{
				ECollisionDirection colDirection;
				float collisionTime = sweptAABB(box, boxOther, colDirection, dt);
				if (collisionTime < 1.0f && collisionTime > 0.0) //collisiontime > 0 &&
				{
					OnColideMovingPlatform((MovingPlatform*) other, dt, colDirection, collisionTime, isOnMovingPlatform);
					//this->x += (other->vX)*15;
					//this->vX = other->vX;
				}
			}
		}
	}

#pragma endregion

	//fallBox.w = fallBox.h + 10;
	for (_itBegin = listObject.begin(); _itBegin != listObject.end(); _itBegin++)
	{
		GameObject* other = (*_itBegin);
		if (other->active) {
			(other)->SetActive(x, y);
			other->Update(x, y, dt);

			Box box = this->GetBox();
			Box boxOther = other->GetBox();
			box.vx -= boxOther.vx;
			box.vy -= boxOther.vy;
			Box broadphasebox = getSweptBroadphaseBox(box, dt);
			if ((*_itBegin)->id == EnumID::BonePillar_ID || (*_itBegin)->id == EnumID::Medusa_ID)
				(*_itBegin)->CollSimon(this, dt);

			if ((other->id == EnumID::StairBotRight_ID || other->id == EnumID::StairTopRight_ID || other->id == EnumID::StairBotLeft_ID || other->id == EnumID::StairTopLeft_ID))
			{
				if (AABBCheck(fallBox, boxOther)) {
					onCollideStair((Stair*)other);
					if (box.y - box.h + 10 - other->y >= 0 && !isJump && (other->id == EnumID::StairTopRight_ID || other->id == EnumID::StairTopLeft_ID)) {
						onTopStair = true;
					}
								}
			}

			if (AABBCheck(broadphasebox, boxOther))
			{

				ECollisionDirection colDirection;
				float collisionTime = sweptAABB(box, boxOther, colDirection, dt);
				if (collisionTime < 1.0f && collisionTime > 0.0) //collisiontime > 0 &&
				{
					if (other->id == EnumID::StairTopRight_ID) {
						int a = 0;
					}
					switch (other->id)
					{
					case EnumID::StairBotLeft_ID:
					case EnumID::StairBotRight_ID:
					case EnumID::StairTopLeft_ID:
					case EnumID::StairTopRight_ID:
						onCollideStair((Stair*)other);
						break;
					case EnumID::Tele_ID:
					case EnumID::Door_ID:
						onCollideDoor((Door*)other, colDirection, collisionTime, dt);
						break;
					case EnumID::Boomerang_Weapon_ID:
						other->active = false;
						//other->Update(dt);
						break;
					case EnumID::BigHeart_ID:
						hearts += 5;
						other->Remove();
						break;
					case EnumID::SmallHeart_ID:
						hearts += 1;
						other->Remove();
						break;
					case EnumID::MoneyBag400_ID:
						point += 400;
						other->Remove();
						break;
					case EnumID::MoneyBag700_ID:
						point += 700;
						other->Remove();
						break;
					case EnumID::PorkChop_ID:
						hp += 10;
						other->Remove();
						break;
					case EnumID::Axe_ID:
						weaponID = EnumID::Axe_ID;
						other->Remove();
						break;
					case EnumID::Boomerang_ID:
						weaponID = EnumID::Boomerang_ID;
						other->Remove();
						break;
					case EnumID::HolyWater_ID:
						weaponID = EnumID::HolyWater_ID;
						other->Remove();
						break;
					case EnumID::Knife_ID:
						weaponID = EnumID::Knife_ID;
						other->Remove();
						break;
					case EnumID::SpiritBall_ID:
						hp = 20;
						isPickUpSpiritBall = true;
						Sound::GetInstance()->PlayEffectSound(EEffectSound::ESpiritBallSound);
						break;
					case EnumID::Cross_ID:
						isUseCross = true;
						Sound::GetInstance()->PlayEffectSound(EEffectSound::ECrossSound);
					default:
						break;
					}	
				}
				if (other->type == ObjectType::Enemy_Type && immuteTime == 0)
				{
					this->ReceiveDamage(other->damage);
					KnockBack();
					Sound::GetInstance()->PlayEffectSound(EEffectSound::EHurtedSound);
				}

				if (other->type == ObjectType::Item)
				{
					Sound::GetInstance()->PlayEffectSound(EEffectSound::ECollectItemSound);
				}
			}
		}	
	}

	if (!isCollideBottom && !isJump && !onStair && !isKnockedBack && !onTopStair && !isOnMovingPlatform) {
		fall();
	}

}

void Simon::Die(int &time)
{
	if (isDeath)
	{
		canPress = false;
		time -= 1;
		simonDeath->SelectIndex(0);
		if (time == 0)
		{
			canPress = true;
			isRevival = true;
		}
		Sound::GetInstance()->PlayEffectSound(EEffectSound::EDeathSound);
	}
}

void Simon::fall()
{
	vY = -SPEED_Y * 3;
	canPress = false;
	vX = 0;
}

void Simon::UseBoomerang()
{
	//swID = EnumID::Boomerang_Weapon_ID;
	sub_weapon->push_back(new Boomerang(x, y-13, vLast));
}

void Simon::UseKnife()
{
	//swID = EnumID::Knife_Weapon_ID;
	sub_weapon->push_back(new Knife(x, y-13, vLast));
}

void Simon::UseAxe()
{
	sub_weapon->push_back(new Axe(x, y - 13, vLast));
}

void Simon::UseHolyWater()
{
	sub_weapon->push_back(new HolyWater(x, y - 13, vLast));
}

void Simon::UseWeapon()
{
	if (weaponID == EnumID::None_ID)
		return;
	if (action == Action::SimonUseWeapon || !canPress)
		return;
	if (!isJump)
		vX = 0;
	action = Action::SimonUseWeapon;
	switch (weaponID)
	{
	case EnumID::Axe_Weapon_ID:
		UseAxe();
		break;
	case EnumID::Boomerang_Weapon_ID:
		UseBoomerang();
		break;
	case EnumID::HolyWater_Weapon_ID:
		UseHolyWater();
		break;
	case EnumID::Knife_Weapon_ID:
		UseKnife();
		break;
	default:
		break;
	}
	Sound::GetInstance()->PlayEffectSound(EEffectSound::EMorningStarSound);
}