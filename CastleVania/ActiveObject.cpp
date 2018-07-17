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
	if (sprite == NULL || !active)
		return;
	if (!this->IntoScreen(posX, posY, camera))
	{
		active = false;
		return;
	}
	D3DXVECTOR2 center = camera->Transform(posX, posY);
	if (vX > 0)
		sprite->Draw(center.x, center.y);
	else
		sprite->DrawFlipX(center.x, center.y);
}

void ActiveObject::Collision()
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

bool ActiveObject::IntoScreen(float _posX, float _posY, GCamera* camera)
{
	if (posX + width / 2 <= camera->viewport.x || posX - width / 2 >= camera->viewport.x + G_ScreenWidth
		|| posY + height / 2 <= camera->viewport.y || posY - height / 2 >= camera->viewport.y + G_ScreenHeight)
		return false;
	return true;
}