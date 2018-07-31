#include "Medusa.h"


void Medusa::Initialize()
{
	//Tao cac vi tri boss se di chuyen toi
	listStopPos = vector<D3DXVECTOR2*>();
	listStopPos.pop_back();
	listStopPos.push_back(new D3DXVECTOR2(x - 165, 0));
	listStopPos.push_back(new D3DXVECTOR2(x - 80, 0));
	listStopPos.push_back(new D3DXVECTOR2(x, 0));
	listStopPos.push_back(new D3DXVECTOR2(x + 90, 0));
	listStopPos.push_back(new D3DXVECTOR2(x + 210, 0));

	_previousStopPos = 0;
	_currentStopPos = 0;
	deltaPhi = 0;
	posY0 = y;

	state = EnumMedusaState::stSleeping;
	simonPos = new D3DXVECTOR2(0, 0);
	nextStopPos = new D3DXVECTOR2(0, 0);
	localTime = 0;
	listSnake = new list<ActiveObject*>();

	active = true;
	type = ObjectType::None;
	isGetUp = false;
	hp = 20;
	damage = 10;
	canBeKilled = true;
}

Medusa::Medusa()
{
	this->Initialize();
}

Medusa::Medusa(float posX_, float posY_) :ActiveObject(posX_, posY_, MEDUSA_SPEED, 0, EnumID::Medusa_ID)
{
	Initialize();
	sleepSprite = new GSprite(TextureManager::getInstance()->getTexture(EnumID::Medusa_ID), 4, 4, 1000 / MEDUSA_SLEEP_STATE);
	fightSprite = new GSprite(TextureManager::getInstance()->getTexture(EnumID::Medusa_ID), 0, 3, 1000 / MEDUSA_FIGHT_STATE);
	deadSprite = new GSprite(TextureManager::getInstance()->getTexture(EnumID::HitEffect_ID), 0, 2, 1000 / MEDUSA_DIE_RATE);
}


Medusa::~Medusa()
{
	delete listSnake;
}

void Medusa::Stoping(int deltaTime)
{
	this->fightSprite->Update(deltaTime);
	localTime = deltaTime;
	if (localTime > 1000)	//Bay sang vi tri khac
	{
		float deltaX = x - simonPos->x;						//khang cach tu Boss toi Simon
		float snake_vX = (-deltaX / abs(deltaX))*SNAKE_SPEED;	//Snake	luon chay ve huong Simon
		localTime = 0;
		switch (_currentStopPos)
		{
		case 0:
		{
			_previousStopPos = _currentStopPos;
			int rd = rand() % 2;
			if (rd == 0)
				_currentStopPos = 2;
			else
				_currentStopPos = 4;
			if (vX < 0)
				vX = -vX;
		}
		break;
		case 1:
		{
			_previousStopPos = _currentStopPos;
			_currentStopPos = 0;
			
			listSnake->push_back(new Snake(x, y, snake_vX, -0.2f, EnumID::Snake_ID));	//Tha Snake
		}
		break;
		case 2:
		{
			_previousStopPos = _currentStopPos;
			if (deltaX > 0)
			{
				_currentStopPos = 1;
				if (vX > 0)
					vX = -vX;
			}
			else
			{
				_currentStopPos = 3;
				if (vX < 0)
					vX = -vX;
			}
		}
		break;
		case 3:
		{
			_previousStopPos = _currentStopPos;
			_currentStopPos = 4;
			listSnake->push_back(new Snake(x, y, snake_vX, -0.2f, EnumID::Snake_ID)); //Tha Snake
		}
		break;
		case 4:
		{
			_previousStopPos = _currentStopPos;
			int rd = rand() % 2;
			if (rd == 0)
				_currentStopPos = 0;
			else
				_currentStopPos = 2;
			if (vX < 0)
				vX = -vX;
		}
		default:
			break;
		}

		//Bat dau di chuyen sang vi tri moi
		nextStopPos = listStopPos.at(_currentStopPos);
		state = EnumMedusaState::stMoving;
	}
}

// Kiem tra boss di ra xa hay gan lai NextStopPos
bool Medusa::LeaveStopPos(D3DXVECTOR2 _boss, D3DXVECTOR2 _nextStopPos)
{
	float deltaX = _boss.x - _nextStopPos.x;
	if (deltaX*vX>0)
		return true;			//di ra xa
	return false;				//di gan lai
}

void Medusa::Moving(int deltaTime_)
{
	//Neu di xa nextStopPos thi phai ngung lai
	if (LeaveStopPos(D3DXVECTOR2(x, y), *this->nextStopPos))
	{
		this->state = EnumMedusaState::stStop;
		return;
	}
	//Neu khong
	x += vX * deltaTime_;
	y = posY0 + A * cos(2 * PI*deltaTime_ / T + deltaPhi); // Phuong trinh chuyen dong duong hinh sin x = 2pi. t/ lamda
	deltaPhi += 2 * PI*deltaTime_ / T;
	fightSprite->Update(deltaTime_);
}

void Medusa::Deading(int deltaTime)
{
	deadSprite->Update(deltaTime);
	localTime += deltaTime;
	if (localTime >= DEAD_TIME)
	{
		active = false;
		this->state = EnumMedusaState::stRemove;
	}
}

void Medusa::GetUp()
{
	this->state = EnumMedusaState::stStop;
	if (!isGetUp)
	{
		//Sound::GetInst()->RemoveAllBGM();
		//Sound::GetInst()->PlayBGSound(EBGSound::EBoss);
		type = ObjectType::Enemy_Type;
		isGetUp = true;
		G_RightCamera = G_LeftCamera + G_ScreenWidth;
	}
}


//Chua xu ly
void Medusa::ReceiveDamage(int damege)
{

}

void Medusa::UpdateSnakes(int deltaTime_)
{
	list<ActiveObject*>::iterator it = listSnake->begin();
	while (it != listSnake->end())
	{
		if (!(*it)->active)
			listSnake->erase(it++);
		else
		{
			(*it)->Update(deltaTime_);
			++it;
		}
	}

}

void Medusa::DrawSnakes(GCamera* camera_)
{
	for (list<ActiveObject*>::iterator iter = listSnake->begin(); iter != listSnake->end(); iter++)
	{
		ActiveObject* tempSnake = (*iter);
		tempSnake->Draw(camera_);
	}
}

void Medusa::Update(int deltaTime)
{
	switch (state)
	{
	case stSleeping:
		break;
	case stMoving:
		Moving(deltaTime);
		break;
	case stStop:
		Stoping(deltaTime);
		break;
	case stDead:
		Deading(deltaTime);
	default:
		break;
	}
	UpdateSnakes(deltaTime);
}

void Medusa::Update(int t, D3DXVECTOR2* _simonPos)
{
	this->simonPos = _simonPos;
	this->Update(t);
}

void Medusa::Draw(GCamera* camera_)
{
	D3DXVECTOR2 center = camera_->Transform(x, y);
	switch (state)
	{
	case stSleeping:
		sleepSprite->Draw(center.x, center.y);
		break;
	case stStop:case stMoving:
		// draw the boss
		fightSprite->Draw(center.x, center.y);
		// draw the snake
		this->DrawSnakes(camera_);
		break;
	case stDead:
		//ve 6 dom lua nho tai 6 vi tri de tao thanh dam lua lon
		deadSprite->Draw(center.x - 40, center.y);
		deadSprite->Draw(center.x, center.y);
		deadSprite->Draw(center.x + 40, center.y);

		deadSprite->Draw(center.x - 40, center.y - 15);
		deadSprite->Draw(center.x, center.y - 15);
		deadSprite->Draw(center.x + 40, center.y - 15);
		break;
	case stRemove:
		break;
	default:
		break;
	}
}

bool Medusa::StateCancel()
{
	if (this->state == EnumMedusaState::stRemove)
		return true;
	return false;
}

int Medusa::GetHp()
{
	return hp;
}

void Medusa::setDead()
{
	this->state = EnumMedusaState::stDead;
}

void Medusa::Collision()
{

}