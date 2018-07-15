#include "ActiveObject.h"



ActiveObject::ActiveObject() : GameObject()
{
	canBeKilled = true;
}

ActiveObject::ActiveObject(float _posX, float _posY, float _vX, float _vY, EnumID id) :
	GameObject(_posX, _posY, id)
{
	vX = _vX;
	vY = _vY;
	canMove = true;
	active = true;
}


ActiveObject::~ActiveObject()
{
}

void ActiveObject::Update(int deltaTime)
{
	//chua dinh nghia
}

void ActiveObject::Update(Box playerBox, int deltaTime)
{
	//chua dinh nghia
}

Box ActiveObject::GetBox()
{
	Box box(posX - width / 2, posY - height / 2, width, height, vX, 0);
	return box;
}

void ActiveObject::Draw(GCamera* camera)
{
	//chua dinh nghia
}

void ActiveObject::Collision(list<GameObject*> obj, int deltaTime)
{
	//chua dinh nghia
}

void ActiveObject::SetActive(float _vX, float _vY)
{
	//chua dinh nghia
}

void ActiveObject::ReceiveDamage(int damage)
{
	//chua dinh nghia
}