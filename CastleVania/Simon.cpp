#include "Simon.h"



Simon::Simon():Enemy()
{
}

Simon::Simon(int _x, int _y) 
	: Enemy(_x, _y, 0, -SPEED_Y, EnumID::Simon_ID)
{
	hp = 10;
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
	canPress = true;
	timeOnStair = 0;
	knockBackTime = 0;
	type = ObjectType::None;

	sub_weapon = new list<Weapon*>();
	swID = EnumID::None_ID;
	live = 10;
	weaponCount = 10;
	weaponID = EnumID::Boomerang_ID;
	morningStar = new MorningStar(x, y, 42);

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

	switch (action)
	{
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
	if (isStop && isLeft)
		vX = 0;
	else 
	{
		isStop = false;
		vX = -SPEED_X;
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
	action = Action::SimonRunRight;
}

void Simon::Jump()
{
 	if (isSit || !canPress || onStair)
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
	if (onStair || onTopStair || !canPress) {
		goDownStair();
		return;
	}
	if (isSit)
		return;
	if (!isJump)
	{
		vX = 0;
		isSit = true;
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
}

void Simon::OnAttack(int deltaTime)
{
	if (isSit && simonSitAttack->GetIndex() >= 17)
	{
		action = Action::SimonSit;
		sprite->Reset();
		morningStar->resetSprite();
	}
	else if ((onStair && upStair && simonAttackUpStair->GetIndex() >= 23) || (onStair && !upStair && simonAttackDownStair->GetIndex() >= 20) || (!isSit && simonAttack->GetIndex() >= 7)) {
		action = Action::SimonStand;
		sprite->Reset();
		morningStar->resetSprite();
	}
	isAttack = true;
	sprite->Update(deltaTime);
	if (isSit) {
		morningStar->update(x, y - 14, deltaTime);
		return;
	}
	morningStar->update(x, y, deltaTime);
}

void Simon::Stop()
{
	vX = 0;
	switch (action)
	{
		case Action::SimonStand:
		case Action::SimonAttack:
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
		y -= AUTO_MOVE_RANGE;
	}
	sprite->Update(dt);
	return false;
}

void Simon::onCollideDoor(Door * obj, ECollisionDirection direction)
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
		isOnBrick = true;
		upStair = false;
		onStair = false;
		timeOnStair = 0;
		isKnockedBack = false;
		canPress = true;
		isJump = false;
		g = GRAVITATIONAL;
		return;
	}

	if (colDirection == ECollisionDirection::Colls_Left && !onStair)
	{
		if (isJump) {
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
		if (isJump) {
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

	if (stair->type == EStairType::BotLeft || stair->type == EStairType::TopLeft) {
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

	switch (stair->type)
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

void Simon::KnockBack()
{
	if (isKnockedBack || !canPress) {
		return;
	}
	if (isLeft) {
		vX = SPEED_X * 10;
	}
	else {
		vX = -SPEED_X * 10;
	}
	g = -GRAVITATIONAL;
	vY = sqrt(-2 * g * MAX_HEIGHT_KNOCKBACK);
	action = Action::SimonHit;
	isKnockedBack = true;
}

void Simon::goDownStair()
{
	if (action == Action::SimonAttack || !canPress) {
		return;
	}

	if (isJump)
		return;

	if (isOnBrick && !colStair && (stair->type != EStairType::BotLeft || stair->type != EStairType::BotRight)) {
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

	if (stair->type == EStairType::BotLeft || stair->type == EStairType::TopLeft || stair->type == EStairType::Left) {
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
	colStair = false;
	onTopStair = false;
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

		// Check if simon is standing on brick
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

	//fallBox.w = fallBox.h + 10;
	for (_itBegin = listObject.begin(); _itBegin != listObject.end(); _itBegin++)
	{
		GameObject* other = (*_itBegin);

		//Set Active cho Enemy
		(other)->SetActive(x, y);
		other->Update(x, y, dt);

		Box box = this->GetBox();
		Box boxOther = other->GetBox();
		box.vx -= boxOther.vx;
		box.vy -= boxOther.vy;
		Box broadphasebox = getSweptBroadphaseBox(box, dt);
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
					onCollideDoor((Door*)other, colDirection);
					break;
				case EnumID::Boomerang_Weapon_ID:
					other->active = false;
					//other->Update(dt);
					break;
				default:
					break;
				}

				if (other->type == ObjectType::Enemy_Type)
				{
					this->ReceiveDamage((other)->damage);
					KnockBack();
				}
			}
		}

	}

	if (!isCollideBottom && !isJump && !onStair && !isKnockedBack && !onTopStair) {
		fall();
	}

}

void Simon::Die()
{

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