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

	//onStair = false;
	outStair = false;
	//colBottomStair = false;
	upStair = false;
	downStair = false;
	standOnStair = false;
	colStair = false;


	live = 10;
	weaponCount = 10;
	weaponID = EnumID::Boomerang_ID;

	sprite = new GSprite(TextureManager::getInstance()->getTexture(id), 0, 3, 20);
	simonJum = new GSprite(TextureManager::getInstance()->getTexture(EnumID::Simon_ID), 4, 4, 300);
	simonAttack = new  GSprite(TextureManager::getInstance()->getTexture(EnumID::Simon_ID), 5, 8, 1000 / SIMON_FIGHT_RATE);
	simonOnStair = new GSprite(TextureManager::getInstance()->getTexture(EnumID::Simon_ID), 10, 13, 320);
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
		if (vX >0 || vLast > 0)
		{
			if (action == Action::Attack)
			{
				//simonAttack->DrawFlipX(center.x, center.y);
				simonAttack->DrawFlipX(pos.x, pos.y);
				return;
			}
			if (onStair)
			{
				if (stairType == EStairType::BotRight || stairType == EStairType::TopLeft)
					simonOnStair->DrawFlipX(pos.x, pos.y);
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
			if (onStair)
			{
				if (stairType == EStairType::BotLeft || stairType == EStairType::TopRight)		//Hình như không cần dòng này
					simonOnStair->Draw(pos.x, pos.y);
			}
			//sprite->Draw(center.x, center.y);
			sprite->Draw(pos.x, pos.y);
		}
	}
}

void Simon::Update(int deltaTime)
{
	/*
	if (isOnBrick == false)
	{
		vY = -SPEED_Y;
		//y += vY * deltaTime;
		//return;
	}
	*/
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
	//if (colBottomStair)
		UpdateStair(deltaTime);

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
				this->y = other.y + this->height -2;
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
				switch (other->id)
				{
				case EnumID::Brick_ID:
					StandBrick(boxOther, dt, colDirection, collisionTime);
					break;
				case EnumID::StairBotLeft_ID:
				case EnumID::StairBotRight_ID:
				case EnumID::StairTopLeft_ID:
				case EnumID::StairTopRight_ID:
					TakeOnStairs(other, dt);
					break;
				default:
					break;
				}
			}
		}
		
	}
}

void Simon::SetUpStair()
{
	if (stairType == EStairType::TopRight)
	{
		vX = vLast = -1;
		stairType = EStairType::BotRight;
	}
	if (stairType == EStairType::TopLeft)
	{
		vX = vLast = 1;
		stairType = EStairType::BotLeft;
	}
}

void Simon::SetDownStair()
{
	if (stairType == EStairType::BotRight)
	{
		vX = vLast = -1;
		stairType = EStairType::TopRight;
	}
	if (stairType == EStairType::BotLeft)
	{
		vX = vLast = 1;
		stairType = EStairType::TopLeft;
	}
}

void Simon::OutStair()
{
	if (upStair || downStair)
	{
		upStair = false;
		downStair = false;
		onStair = false;
		colStair = false;
		vX = 0;
		vY = -SPEED_Y;
		sprite->SelectIndex(0);

		switch (stair->id)
		{
		case EnumID::StairBotLeft_ID:
			stairType = EStairType::BotLeft;
			break;
		case EnumID::StairBotRight_ID:
			stairType = EStairType::BotRight;
			break;
		case EnumID::StairTopRight_ID:
			stairType = EStairType::TopRight;
			break;
		case EnumID::StairTopLeft_ID:
			stairType = EStairType::TopLeft;
			break;
		default:
			break;
		}
	}
}

bool Simon::OnStair()
{
	if ((stair->y == y - 14 && colStair &&
		(stair->id == EnumID::StairTopRight_ID || stair->id == EnumID::StairTopLeft_ID)) || onStair)
		return true;
	return false;
}

void Simon::ResetStair()
{
	if (upStair || downStair)
		upStair = downStair = false;
	colStair = false;
}

void Simon::UpStair()
{
	if (!downStair)
	{
		upStair = true;
		if (onStair)
			SetUpStair();
	}
	if (isJump || action == Action::Attack)
		return;
	//if (colBottomStair)		//chưa hiểu lắm
	//	return;

	if (abs(rangeStair) <= 40)		//Cách 1 khoảng <= 40 khi nhấn lên sẽ di chuyển lại đầu cầu thang
	{
		if (colStair && stair->y == this->GetBox().y -14 && (stair->id == EnumID::StairBotLeft_ID || stair->id == EnumID::StairBotRight_ID))
		{
			if (!colBottomStair)			//bắt đầu đi lên
				colBottomStair = true;
			else
			{
				onStair = true;
				timeOnStair = 0;
			}

			if (rangeStair != 0)			//Chưa tới vị trí đầu cầu thang
				onStair = false;
			else
			{
				onStair = true;
				SetUpStair();
				simonOnStair->SelectIndex(13);
				timeOnStair = 0;
			}
		}
	}
	else
		colStair = false;
}

void Simon::DownStair()
{
	if (!upStair)
	{
		downStair = true;
		if (onStair)
			SetDownStair();
	}

	if (isJump || action == Action::Attack)
		return;
	if (colBottomStair)		//chưa hiểu lắm
		return;

	if (abs(rangeStair) <= 40)
	{
		if (colStair && stair->y == y - 14 && (stair->id == EnumID::StairTopRight_ID || stair->id == EnumID::StairTopLeft_ID))
		{
			if (!colBottomStair)
				colBottomStair = true;
			else
			{
				onStair = true;
				timeOnStair = 0;
			}

			if (rangeStair != 0)
				onStair = false;
			else
			{
				onStair = true;
				SetDownStair();
				simonOnStair->SelectIndex(11);
				timeOnStair = 0;
			}
		}
	}
	else
		colStair = false;
}

void Simon::UpdateStair(int dt)
{
	if (!onStair)
	{
		if (colBottomStair)
		{
			if (rangeStair < 0)			//Simon bên trái đầu cầu thang
			{
				vX = vLast = 1;
				this->x += 1;
				rangeStair += 1;		//Simon luôn hướng về vị trí rangeStair = 0
			}
			if (rangeStair > 0)			//Siomon bên phải đầu cầu thang
			{
				vX = vLast = -1;
				this->x -= 1;
				rangeStair -= 1;
			}
			if (rangeStair == 0)		//Simon ở điểm rangeStair =0 bắt đầu di chuyển trên cầu thang
			{
				onStair = true;
				timeOnStair = 0;

				switch (stair->id)
				{
				case EnumID::StairBotLeft_ID:
					stairType = EStairType::BotLeft;
					break;
				case EnumID::StairBotRight_ID:
					stairType = EStairType::BotRight;
					break;
				case EnumID::StairTopRight_ID:
					stairType = EStairType::TopRight;
					break;
				case EnumID::StairTopLeft_ID:
					stairType = EStairType::TopLeft;
					break;
				default:
					break;
				}

				//Xét vX
				if (stairType == EStairType::BotRight || stairType == EStairType::TopLeft)
					vX = vLast = 1;
				if (stairType == EStairType::BotLeft || stairType == EStairType::TopRight)
					vX = vLast = -1;

				//Xét vY
				if (stairType == EStairType::BotRight || stairType == EStairType::BotLeft)
				{
					//Vì chỉ đi bước 1 chân lên cầu thang, chân trụ vẫn còn ở mặt đất
					//Nên chỉ cao hơn khi đứng dưới đất 2 đơn vị
					y += 2;			
					simonOnStair->SelectIndex(12);
				}
				if (stairType == EStairType::TopLeft || stairType == EStairType::TopRight)
				{
					//Bước 1 chân xuống cầu thang, chân trụ khuỵu xuống
					//Nên sẽ thấp hơn khi đứng ở mặt đất 16 đơn vị (bằng chênh lệch giữa ngồi và đứng)
					y -= 16;		
					simonOnStair->SelectIndex(10);
				}
			}
			sprite->Update(dt);
		}
		else if (outStair)	//Ra khỏi cầu thang
		{
			colStair = false;	//Không va chạm với cầu thang nữa
			sprite->SelectIndex(0);
			stairType = EStairType::NoneType;
			//action = Action::Stand;		//không chắc
		}
		
	}
	else			//Không ở đầu cầu thang => đang đi trên cầu thang
	{
		if (upStair)		//Đang đi lên
		{
			if (stairType == EStairType::BotRight)		//Đi lên bên phải
			{
				timeOnStair += 1;		//Thời gian đi trên cầu thang bắt đầu được tính
				vX = vLast = 1;

				//Nếu timeOnStair = 10 thì simon bước được 1 bậc rồi dừng lại
				//Nếu nhấn phím lên 1 lần nữa, thì sẽ bước 1 bậc nữa
				if (timeOnStair <= 10)
				{
					y += 1.6;
					x += 1.6;
					if (timeOnStair > 1 && timeOnStair < 6)
						simonOnStair->SelectIndex(13);		//Động tác bước chân trước lên
					else
						simonOnStair->SelectIndex(12);		//Động tác bước chân sau lên theo

					if (timeOnStair == 10)					//Hoàn thành 1 bậc
					{
						standOnStair = true;				//Sẽ đứng trên cầu thang
						timeOnStair = 0;					//Reset timeOnStair để thực hiện động tác tiếp theo
						return;
					}
				}
				
			}
			if (stairType == EStairType::BotLeft)		//Đi lên bên trái
			{
				timeOnStair += 1;		//Thời gian đi trên cầu thang bắt đầu được tính
				vX = vLast = -1;
				if (timeOnStair <= 10)
				{
					y += 1.6;
					x -= 1.6;
					if (timeOnStair > 1 && timeOnStair < 6)
						simonOnStair->SelectIndex(13);		
					else
						simonOnStair->SelectIndex(12);		

					if (timeOnStair == 10)					
					{
						standOnStair = true;				
						timeOnStair = 0;					
						return;
					}
				}
			}	
		}
		else if (downStair)								//Đi xuống
		{

			if (stairType == EStairType::TopLeft)
			{
				timeOnStair += 1;
				vX = vLast = 1;

				if (timeOnStair <= 10)
				{
					x += 1.6;
					y -= 1.6;
					if (timeOnStair > 1 && timeOnStair < 6)
						simonOnStair->SelectIndex(10);
					else
						simonOnStair->SelectIndex(12);

					if (timeOnStair == 10)
					{
						standOnStair = true;
						timeOnStair = 0;
						return;
					}
				}		
			}
			if (stairType == EStairType::TopLeft)
			{
				timeOnStair += 1;
				vX = vLast = -1;
				if (timeOnStair <= 10)
				{
					x -= 1.6;
					y -= 1.6;
					if (timeOnStair > 1 && timeOnStair < 6)
						simonOnStair->SelectIndex(10);
					else
						simonOnStair->SelectIndex(12);

					if (timeOnStair == 10)
					{
						standOnStair = true;
						timeOnStair = 0;
						return;
					}
				}
			}
		}
	}
}

void Simon::TakeOnStairs(GameObject *other, int dt)
{
	Box simon = this->GetBox();
	Box boxStair = other->GetBox();
	stair = other;

	//Nếu biến 
	if (!colStair && !isJump)
		colStair = true;
	switch (other->id)
	{
		case EnumID::StairBotRight_ID:
		{
			if (!colBottomStair)
				rangeStair = simon.x - (boxStair.x);	// - k);	k là số để điều chỉnh cho hợp lý với cầu thang
			if (upStair && onStair)
				stairType = EStairType::BotRight;
			/*
			float compareHeight = (simon.y - simon.h) - (boxStair.y - boxStair.h);
			if (compareHeight == 0 && stairType == EStairType::TopRight)
			{
				outStair = true;
				OutStair();
			}
			*/
		}
		break;
		case EnumID::StairBotLeft_ID:
		{
			if (!colBottomStair)
				rangeStair = simon.x - (boxStair.x);	// -k);		k là số để điều chỉnh cho hợp lý với cầu thang
			if (upStair&& onStair)
				stairType = EStairType::BotLeft;
			/*
			float compareHeight = (simon.y - simon.h) - (boxStair.y - boxStair.h);
			if (compareHeight == 0 && stairType == EStairType::TopLeft)
			{
				outStair = true;
				OutStair();
			}
			*/
		}
		break;
		case EnumID::StairTopRight_ID:
		{
			if (!colBottomStair)
				rangeStair = simon.x - (boxStair.x);	// -k);		k là số để điều chỉnh cho hợp lý với cầu thang
			if (upStair&& onStair)
				stairType = EStairType::TopRight;
			/*
			float compareHeight = (simon.y - simon.h) - (boxStair.y - boxStair.h);
			if (compareHeight == 0 && stairType == EStairType::BotRight)
			{
				outStair = true;
				OutStair();
			}
			*/
		}
		break;
		case EnumID::StairTopLeft_ID:
		{
			if (!colBottomStair)
				rangeStair = simon.x - (boxStair.x);	// -k);		k là số để điều chỉnh cho hợp lý với cầu thang
			if (upStair&& onStair)
				stairType = EStairType::TopLeft;
			/*
			float compareHeight = (simon.y - simon.h) - (boxStair.y - boxStair.h);
			if (compareHeight == 0 && stairType == EStairType::BotLeft)
			{
				outStair = true;
				OutStair();
			}
			*/
		}
		break;
		default:
			break;
	}

}