#include "QGameObject.h"


QGameObject::QGameObject(void)
{
	
}

void QGameObject::RemoveAllObject()
{
	_dynamicObject->clear();
}

int QGameObject::RemoveAllObjectInCamera(D3DXVECTOR2 viewport)
{
	int score = 0;
	list<GameObject*>::iterator it = _dynamicObject->begin();
	while (it != _dynamicObject->end())
	{
		GameObject* other = (*it);
		if (other->active && !(other->posX + other->width / 2 <= viewport.x
			|| other->posX - other->width / 2 >= viewport.x + G_ScreenWidth
			|| other->posY + other->height / 2 <= viewport.y - G_ScreenHeight
			|| other->posY - other->height / 2 >= viewport.y))
		{
			if (other->type == ObjectType::Enemy_Type)
			{
				switch (other->id)
				{
				
				default:
					score += other->point;
					_dynamicObject->erase(it++);
					break;
				}
			}
			else ++it;
		}
		else ++it;
	}
	return score;
}
//Được gọi khi load Stage
//Filename là tên file Stage
QGameObject::QGameObject(string fileName)
{
	ifstream map(fileName);

	// GameObject :_staticObject,_dynamicObject
	_staticObject = new list<GameObject*>();
	_dynamicObject = new list<GameObject*>();

	if (map.is_open())
	{
		float posX, posY; int width, height;
		int count;
		map >> count >> width >> height;
		int id;
		int x = 0;
		// duyệt từng dòng của file Stage
		for (int i = 0; i < count; i++)
		{
			float enumValue;
			map >> id >> posX >> posY >> width >> height;

			// ứng với giá trị value tương ứng để khởi tạo các object tương tứng
			switch (id)
			{

			case EnumID::Brick_ID:
				_staticObject->push_back(new Brick(posX, posY, width, height, false));
				break;
			case EnumID::StairUpLeft_ID:
				_staticObject->push_back(new Stair(posX, posY, width + 32, height, EnumID::StairUpLeft_ID));
				break;
			case EnumID::StairUpRight_ID:
				_staticObject->push_back(new Stair(posX, posY, width + 32, height, EnumID::StairUpRight_ID));
				break;
			case EnumID::Candle_ID:
				_staticObject->push_back(new Candle(posX, posY));
				break;
			case EnumID::Breakable_ID:
				_staticObject->push_back(new Brick(posX, posY, width, height, true));
				break;
			case EnumID::Door_ID:
				_staticObject->push_back(new Door(posX, posY));
				break;
			case EnumID::MovingPlatform_ID:
				_dynamicObject->push_back(new MovingPlatform(posX, posY));
				break;
			case EnumID::Tele_ID:
				_staticObject->push_back(new Tele(posX, posY, width, height));
				break;
			case EnumID::Trap_ID:
				_dynamicObject->push_back(new Trap(posX, posY));
				break;
			case EnumID::Count_Dracula_ID:
				_dynamicObject->push_back(new BonePillar(posX, posY));
				break;
			case EnumID::Medusa_ID:
				_medusa = new Medusa(posX, posY, EnumID::Medusa_ID);
				_dynamicObject->push_back(_medusa);
				break;
			case EnumID::MedusaHead_ID:
				_dynamicObject->push_back(new MovingPlatform(posX, posY));
				break;
			case EnumID::Ghost_ID:
				_staticObject->push_back(new Ghost(posX, posY));
			break;
			case EnumID::Bat_ID:
				_staticObject->push_back(new Ghost(posX, posY));
				break;
			case EnumID::BonePillar_ID:
				_staticObject->push_back(new Ghost(posX, posY));
				break;
			case EnumID::Eagle_ID:
				/*_staticObject->push_back(new Eagle(posX, posY, width, height, EnumID::DoorLeft_ID));*/
				break;
			case EnumID::PhantomBat_ID:
				_staticObject->push_back(new PhantomBat(posX, posY));
				break;
			case EnumID::Pleaman_ID:
				/*_staticObject->push_back(new Door(posX, posY, width, height, EnumID::TeleUp_ID));*/
				break;
			case EnumID::Skeleton_ID:
				//_staticObject->push_back(new Door(posX, posY, width, height, EnumID::TeleDown_ID));
				break;
			case EnumID::SpearGuard_ID:
				_dynamicObject->push_back(new SpearGuard(posX, posY));
				break;
			case EnumID::Axe_ID:
			case EnumID::BigHeart_ID:
			case EnumID::Boomerang_ID:
			case EnumID::Knife_ID:
			case EnumID::Cross_ID:
			case EnumID::Crown_ID:
			case EnumID::DoubleShot_ID:
			case EnumID::FireBomb_ID:
			case EnumID::MoneyBag400_ID:
			case EnumID::MoneyBag700_ID:
			case EnumID::MorningStar_ID:
			case EnumID::PorkChop_ID:
			case EnumID::SmallHeart_ID:
			case EnumID::SpiritBall_ID:
			case EnumID::StopWatch_ID:
			case EnumID::TreasureChest_ID:
				_staticObject->push_back(new RewardItem(posX, posY, width, height, static_cast<EnumID>(id)));
				break;
			}
		}
	}
	_pausing = false;
	_startToPauseTime = 0;
}

Medusa* QGameObject::getMedusa()
{
	return _medusa;
}

D3DXVECTOR2 QGameObject::GetPosDoor()
{
	return posDoor;
}

void QGameObject::Draw(GCamera *camera)
{
	for (list<GameObject*>::iterator i = _staticObject->begin(); i != _staticObject->end(); i++)
	{
		GameObject* obj = (*i);
	
		if (obj->active)
		{
			obj->Draw(camera);
		}
	}

	for (list<GameObject*>::iterator i = _dynamicObject->begin(); i != _dynamicObject->end(); i++)
	{
		GameObject* obj = (*i);
	
		if (obj->active)
		{
			obj->Draw(camera);
		}
	}
}

// Gọi về hàm va chạm của lớp con
void QGameObject::Collision(int dt)
{
	for (list<GameObject*>::reverse_iterator i = _staticObject->rbegin(); i != _staticObject->rend(); i++)
	{
		if ((*i)->canMove)
		{
			(*i)->Collision((*_staticObject), dt);
		}
	}
	for (list<GameObject*>::iterator i = _dynamicObject->begin(); i != _dynamicObject->end(); i++)
	{
		if ((*i)->active)
		{
			(*i)->Collision((*_staticObject), dt);
		}
	}
}
// Gọi về hàm update của từng game object để vẽ hình
void QGameObject::Update(int deltaTime)
{
	list<GameObject*>::iterator it = _staticObject->begin();
	while (it != _staticObject->end())
	{	
		{
			(*it)->Update(deltaTime);
			++it;
		}
	}

	it = _dynamicObject->begin();
	while (it != _dynamicObject->end())
	{
		if  (!IsPausing() || (IsPausing() && (*it)->type != ObjectType::Enemy_Type)) {
			if ((*it)->id == EnumID::Medusa_ID)
			{
				if (((Medusa*)*it)->StateCancel())
				{
					//_dynamicObject->push_back(new ((*it)->posX, (*it)->posY));
					_dynamicObject->erase(it++);
				}
				else ++it;
			}
			else {

				if ((*it)->active)
				{

					
						(*it)->Update(deltaTime);
					
				}
				it++;

			}
		}
		else 
		++it;
	}
}
void QGameObject::Update(int playerX, int playerY, int deltaTime)
{
	list<GameObject*>::iterator it = _staticObject->begin();
	while (it != _staticObject->end())
	{
		{
			(*it)->Update(deltaTime);
			++it;
		}
	}

	it = _dynamicObject->begin();
	while (it != _dynamicObject->end())
	{
		if (!IsPausing() || (IsPausing() && (*it)->type != ObjectType::Enemy_Type)) {
			if ((*it)->id == EnumID::Medusa_ID)
			{
				if (((Medusa*)*it)->StateCancel())
				{
					/*_dynamicObject->push_back(new MagicalBall((*it)->posX, (*it)->posY));*/
					_dynamicObject->erase(it++);
				}
				else ++it;
			}
			else {

				if ((*it)->active)
				{

					if ((*it)->neededPlayerPosition) {
						(*it)->Update(playerX, playerY, deltaTime);
					}
					else {
						(*it)->Update(deltaTime);
					}
				}
				it++;

			}
		}
		else
			++it;
	}
}
// Neu IsPausing == false -> Game chay binh thuong
bool QGameObject::IsPausing()
{
	if (!_pausing)
		return false;
	DWORD now = GetTickCount();
	DWORD deltaTime = now - _startToPauseTime;
	if (deltaTime >= 1200)
	{
		_pausing = false;
		return false;
	}
	return true;
}
void QGameObject::PauseUpdate() {
	_pausing = true;
	_startToPauseTime = GetTickCount();
}

QGameObject::~QGameObject(void)
{
}
