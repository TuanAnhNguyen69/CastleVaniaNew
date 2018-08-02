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

	live = 10;
	weaponCount = 10;
	weaponID = EnumID::Boomerang_ID;

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
				if (stairType == EStairType::UpRight || stairType == EStairType::DownRight)
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
				if (stairType == EStairType::UpLeft || stairType == EStairType::UpLeft)		//Hình như không cần dòng này
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
	if (colBottomStair)
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
				case EnumID::StairDownLeft_ID:
				case EnumID::StairDownRight_ID:
				case EnumID::StairUpLeft_ID:
				case EnumID::StairUpRight_ID:
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
	if (stairType == EStairType::DownLeft)
	{
		vX = vLast = -1;
		stairType = EStairType::UpRight;
	}
	if (stairType == EStairType::DownRight)
	{
		vX = vLast = 1;
		stairType = EStairType::UpLeft;
	}
}

void Simon::SetDownStair()
{
	if (stairType == EStairType::UpRight)
	{
		vX = vLast = -1;
		stairType = EStairType::DownLeft;
	}
	if (stairType == EStairType::UpLeft)
	{
		vX = vLast = 1;
		stairType = EStairType::DownRight;
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
		case EnumID::StairUpLeft_ID:
			stairType = EStairType::UpLeft;
			break;
		case EnumID::StairUpRight_ID:
			stairType = EStairType::UpRight;
			break;
		case EnumID::StairDownLeft_ID:
			stairType = EStairType::DownLeft;
			break;
		case EnumID::StairDownRight_ID:
			stairType = EStairType::DownRight;
			break;
		default:
			break;
		}
	}
}

bool Simon::OnStair()
{
	if ((stair->y = y - 14 && colStair &&
		(stair->id == EnumID::StairDownLeft_ID || stair->id == EnumID::StairDownRight_ID)) || onStair)
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
	if (colBottomStair)		//chưa hiểu lắm
		return;

	if (abs(rangeStair) <= 40)		//Cách 1 khoảng <= 40 khi nhấn lên sẽ di chuyển lại đầu cầu thang
	{
		if (colStair && stair->y == y && (stair->id == EnumID::StairUpLeft_ID || stair->id == EnumID::StairUpRight_ID))
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
		onStair = false;
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
		if (colStair && stair->y == y - 14 && (stair->id == EnumID::StairDownLeft_ID || stair->id == EnumID::StairDownRight_ID))
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
			if (rangeStair > 0)			//Simon bên phải đầu cầu thang
			{
				vX = vLast = 1;
				x += 1;
				rangeStair += 1;		//Simon luôn hướng về vị trí rangeStair = 0
			}
			if (rangeStair < 0)			//Siomon bên trái đầu cầu thang
			{
				vX = vLast = -1;
				x -= 1;
				rangeStair -= 1;
			}
			if (rangeStair == 0)		//Simon ở điểm rangeStair =0 bắt đầu di chuyển trên cầu thang
			{
				onStair = true;
				timeOnStair = 0;

				switch (stair->id)
				{
				case EnumID::StairUpLeft_ID:
					stairType = EStairType::UpLeft;
					break;
				case EnumID::StairUpRight_ID:
					stairType = EStairType::UpRight;
					break;
				case EnumID::StairDownLeft_ID:
					stairType = EStairType::DownLeft;
					break;
				case EnumID::StairDownRight_ID:
					stairType = EStairType::DownRight;
					break;
				default:
					break;
				}

				//Xét vX
				if (stairType == EStairType::UpRight || stairType == EStairType::DownRight)
					vX = vLast = 1;
				if (stairType == EStairType::UpLeft || stairType == EStairType::DownLeft)
					vX = vLast = -1;

				//Xét vY
				if (stairType == EStairType::UpRight || stairType == EStairType::UpLeft)
				{
					//Vì chỉ đi bước 1 chân lên cầu thang, chân trụ vẫn còn ở mặt đất
					//Nên chỉ cao hơn khi đứng dưới đất 2 đơn vị
					y += 2;			
					simonOnStair->SelectIndex(12);
				}
				if (stairType == EStairType::DownRight || stairType == EStairType::DownLeft)
				{
					//Bước 1 chân xuống cầu thang, chân trụ khuỵu xuống
					//Nên sẽ thấp hơn khi đứng ở mặt đất 16 đơn vị (bằng chênh lệch giữa ngồi và đứng)
					y -= 16;		
					simonOnStair->SelectIndex(10);
				}
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
			if(upStair)		//Đang đi lên
			{ 
				timeOnStair += 1;		//Thời gian đi trên cầu thang bắt đầu được tính
				y += 1.6;

				//Nếu timeOnStair = 10 thì simon bước được 1 bậc rồi dừng lại
				//Nếu nhấn phím lên 1 lần nữa, thì sẽ bước 1 bậc nữa
				if (timeOnStair <= 10)
				{
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

				if (stairType == EStairType::UpRight)		//Đi lên bên phải
				{
					vX = vLast = 1;
					x += 1.6;
				}
				if (stairType == EStairType::UpLeft)		//Đi lên bên trái
				{
					vX = vLast = -1;
					x -= 1.6;
				}
			}
			else if (downStair)								//Đi xuống
			{
				timeOnStair += 1;
				y -= 1.6;

				if (timeOnStair <= 10)
				{
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
	Box boxOther = other->GetBox();
	stair = other;

	//Nếu biến 
	if (!colStair && !isJump)
		colStair = true;
	switch (other->id)
	{
		case EnumID::StairUpRight_ID:
		{
			if (!colBottomStair)
				rangeStair = x - (other->x);	// - k);	k là số để điều chỉnh cho hợp lý với cầu thang
			if (upStair && onStair)
				stairType = EStairType::UpRight;
			 
			float compareHeight = (simon.y - simon.h) - (boxOther.y - boxOther.h);
			if (compareHeight == 0 && stairType == EStairType::DownLeft)
			{
				outStair = true;
				OutStair();
			}
		}
		break;
		case EnumID::StairUpLeft_ID:
		{
			if (!colBottomStair)
				rangeStair = x - (other->x);	// -k);		k là số để điều chỉnh cho hợp lý với cầu thang
			if (upStair&& onStair)
				stairType = EStairType::UpLeft;

			float compareHeight = (simon.y - simon.h) - (boxOther.y - boxOther.h);
			if (compareHeight == 0 && stairType == EStairType::DownRight)
			{
				outStair = true;
				OutStair();
			}
		}
		break;
		case EnumID::StairDownLeft_ID:
		{
			if (!colBottomStair)
				rangeStair = x - (other->x);	// -k);		k là số để điều chỉnh cho hợp lý với cầu thang
			if (upStair&& onStair)
				stairType = EStairType::DownLeft;

			float compareHeight = (simon.y - simon.h) - (boxOther.y - boxOther.h);
			if (compareHeight == 0 && stairType == EStairType::UpRight)
			{
				outStair = true;
				OutStair();
			}
		}
		break;
		case EnumID::StairDownRight_ID:
		{
			if (!colBottomStair)
				rangeStair = x - (other->x);	// -k);		k là số để điều chỉnh cho hợp lý với cầu thang
			if (upStair&& onStair)
				stairType = EStairType::DownRight;

			float compareHeight = (simon.y - simon.h) - (boxOther.y - boxOther.h);
			if (compareHeight == 0 && stairType == EStairType::UpLeft)
			{
				outStair = true;
				OutStair();
			}
		}
		break;
		default:
			break;
	}

}