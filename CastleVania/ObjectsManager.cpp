#include "ObjectsManager.h"


ObjectsManager::ObjectsManager(void)
{
	quadtree = new QNode(1, new Box(0,0,G_MapWidth, G_MapHeight));
}

void ObjectsManager::RemoveAllObject()
{
	quadtree->Clear();
}

int ObjectsManager::RemoveAllObjectInCamera(D3DXVECTOR2 viewport)
{
	int score = 0;
	list<GameObject*>::iterator it = inSightObjects->begin();
	while (it != inSightObjects->end())
	{
		GameObject* other = (*it);
		if (other->active && !(other->x + other->width <= viewport.x
			|| other->x >= viewport.x + G_ScreenWidth
			|| other->y + other->height <= viewport.y - G_ScreenHeight
			|| other->y >= viewport.y))
		{
			if (other->type == ObjectType::Enemy_Type)
			{
				switch (other->id)
				{
				
				default:
					score += other->point;
					inSightObjects->erase(it++);
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
ObjectsManager::ObjectsManager(string fileName) : ObjectsManager()
{
	ifstream map(fileName);

	// GameObject :objects,_dynamicObject
	objects = new list<GameObject*>();

	if (map.is_open())
	{
		float posX, posY; int width, height;
		int count;
		map >> count;
		int id;
		int x = 0;


		// duyệt từng dòng của file Stage
		for (int i = 0; i < count; i++)
		{
		float enumValue;
		map >> id >> posX >> posY >> width >> height;
		posY = G_MapHeight - posY;
		if (id > 20) {
			int a = 0;
		}
		// ứng với giá trị value tương ứng để khởi tạo các object tương tứng
		switch (id)
		{

			case EnumID::Brick_ID:
				objects->push_back(new Brick(posX, posY, false));
				break;
			case EnumID::StairLeft_ID:
				objects->push_back(new Stair(posX, posY, width, height, EnumID::StairLeft_ID));
				break;
			case EnumID::StairRight_ID:
				objects->push_back(new Stair(posX, posY, width, height, EnumID::StairRight_ID));
				break;
			case EnumID::StairTopLeft_ID:
				objects->push_back(new Stair(posX, posY, width, height, EnumID::StairTopLeft_ID));
				break;
			case EnumID::StairTopRight_ID:
				objects->push_back(new Stair(posX, posY, width, height, EnumID::StairTopRight_ID));
				break;
			case EnumID::StairBotLeft_ID:
				objects->push_back(new Stair(posX, posY, width, height, EnumID::StairBotLeft_ID));
				break;
			case EnumID::StairBotRight_ID:
				objects->push_back(new Stair(posX, posY, width, height, EnumID::StairBotRight_ID));
				break;
			case EnumID::Candle_ID:
				objects->push_back(new Candle(posX, posY));
				break;
			case EnumID::Breakable_ID:
				objects->push_back(new Brick(posX, posY, true));
				break;
			case EnumID::Door_ID:
				objects->push_back(new Door(posX, posY, width, height));
				break;
			case EnumID::MovingPlatform_ID:
				objects->push_back(new MovingPlatform(posX, posY));
				break;
			case EnumID::Tele_ID:
				objects->push_back(new Tele(posX, posY));
				break;
			case EnumID::Trap_ID:
				//_dynamicObject->push_back(new Trap(posX, posY));
				break;
			case EnumID::Count_Dracula_ID:
				//_dynamicObject->push_back(new Medusa(posX, posY));
				break;
			case EnumID::Medusa_ID:
				//_medusa = new Medusa(posX, posY);
				//_dynamicObject->push_back(_medusa);
				break;
			case EnumID::MedusaHead_ID:
				objects->push_back(new MovingPlatform(posX, posY));
				break;
			case EnumID::Ghost_ID:
				objects->push_back(new Ghost(posX, posY));
			break;
			case EnumID::Bat_ID:
				objects->push_back(new Bat(posX, posY));
				break;
			case EnumID::BonePillar_ID:
				objects->push_back(new BonePillar(posX, posY));
				break;
			case EnumID::Eagle_ID:
				/*objects->push_back(new Eagle(posX, posY, EnumID::DoorLeft_ID));*/
				break;
			case EnumID::PhantomBat_ID:
				objects->push_back(new PhantomBat(posX, posY));
				break;
			case EnumID::Pleaman_ID:
				/*objects->push_back(new Door(posX, posY, EnumID::TeleUp_ID));*/
				break;
			case EnumID::Skeleton_ID:
				//objects->push_back(new Door(posX, posY, EnumID::TeleDown_ID));
				break;
			case EnumID::SpearGuard_ID:
				objects->push_back(new SpearGuard(posX, posY));
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
				objects->push_back(new RewardItem(posX, posY, static_cast<EnumID>(id)));
				break;
			}
		}
	}

	for (auto iterator = objects->begin(); iterator != objects->end(); iterator++) {
		quadtree->Insert(*iterator);
	}
	_pausing = false;
	_startToPauseTime = 0;
}

Medusa* ObjectsManager::getMedusa()
{
	return NULL;
}

D3DXVECTOR2 ObjectsManager::GetPosDoor()
{
	return posDoor;
}

void ObjectsManager::Draw(GCamera *camera)
{
	for (list<GameObject*>::iterator i = objects->begin(); i != objects->end(); i++)
	{ 
		GameObject* obj = (*i);
	
		if (obj->active)
		{
			obj->Draw(camera);
		}
	}
}

// Gọi về hàm va chạm của lớp con
void ObjectsManager::Collision(int dt)
{
	for (list<GameObject*>::reverse_iterator i = inSightObjects->rbegin(); i != inSightObjects->rend(); i++)
	{
		if ((*i)->canMove || (*i)->active)
		{
			(*i)->Collision((*inSightObjects), dt);
		}
	}
}
// Gọi về hàm update của từng game object để vẽ hình
void ObjectsManager::Update(int deltaTime)
{
	list<GameObject*>::iterator it = objects->begin();
	while (it != objects->end())
	{	
		{
			(*it)->Update(deltaTime);
			++it;
		}
	}
}
void ObjectsManager::Update(Simon* simon, int deltaTime)
{
	inSightObjects = new list<GameObject*>();
	quadtree->Retrieve(inSightObjects, simon);
	list<GameObject*>::iterator it = objects->begin();
	while (it != objects->end())
	{
		{
			(*it)->Update(deltaTime);
			++it;
		}
	}
}
// Neu IsPausing == false -> Game chay binh thuong
bool ObjectsManager::IsPausing()
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
void ObjectsManager::PauseUpdate() {
	_pausing = true;
	_startToPauseTime = GetTickCount();
}

ObjectsManager::~ObjectsManager(void)
{
}
