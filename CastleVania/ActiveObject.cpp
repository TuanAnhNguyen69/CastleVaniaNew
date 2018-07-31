#include "ActiveObject.h"



ActiveObject::ActiveObject() : GameObject()
{
	canBeKilled = true;
}

/*
ActiveObject::ActiveObject(float _posX, float _posY, int _width, int _height, float _vX, float _vY, EnumID id) :
	GameObject(_posX, _posY, _width, _height, id)
{
	vX = _vX;
	vY = _vY;
	canMove = true;
	active = true;
}
*/

ActiveObject::ActiveObject(float _x, float _y, float _vX, float _vY, EnumID id) :
	GameObject(_x, _y, id)
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
	if (sprite == NULL || !active)
		return;
	//posX += vX * deltaTime;
	x += vX * deltaTime;
	//if (posX <= width / 2 + 2 || posX >= G_MapWidth - (width / 2 - 2))
	if(x <= width + 2 || x >= G_MapWidth - width + 2)
		vX = -vX;
	//posY += vY * deltaTime;
	y += vY * deltaTime;
	sprite->Update(deltaTime);
}

void ActiveObject::Update(Box playerBox, int deltaTime)
{
	//chua dinh nghia
}

Box ActiveObject::GetBox()
{
	//Box box(posX - width / 2, posY - height / 2, width, height, vX, 0);
	Box box(x, y, width, height, vX, 0);
	return box;
}

void ActiveObject::Draw(GCamera* camera)
{
	if (sprite == NULL || !active)
		return;
	//if (!this->IntoScreen(posX, posY, camera))
	if (!this->IntoScreen(x, y, camera))
	{
		active = false;
		return;
	}
	/*
	D3DXVECTOR2 center = camera->Transform(posX, posY);
	if (vX > 0)
	sprite->Draw(center.x, center.y);
	else
	sprite->DrawFlipX(center.x, center.y);
	*/
	D3DXVECTOR2 pos = camera->Transform(x, y);
	if (vX > 0)
		sprite->Draw(pos.x, pos.y);
	else
		sprite->DrawFlipX(pos.x, pos.y);
}

void ActiveObject::Collision(list<GameObject*> obj, int dt)
{
	list<GameObject*>::iterator _itBegin;
	for (_itBegin = obj.begin(); _itBegin != obj.end(); _itBegin++)
	{
		float moveX = 0;
		float moveY = 0;
		float normalx;
		float normaly;
		GameObject* other = (*_itBegin);
		if (other->id == EnumID::Brick_ID)
		{
			Box box = this->GetBox();
			Box boxOther = other->GetBox();

			if (AABB(box, boxOther, moveX, moveY) == true)
			{
				if (vY < 0)
				{
					//posY += moveY + 20;
					y += moveY;
					vY = 0;
					return;
				}
				/*
				if ((posX - width / 2 + 10) - (other->posX - other->width / 2) <= 0
					|| (posX + width / 2 - 10) - (other->posX + other->width / 2) >= 0)
					vX = -vX;
				*/
				if ((x + 10) - (other->x) <= 0 || (x - 10) - (other->x) >= 0)
					vX = -vX;
			}
			else
				if (AABB(box, boxOther, moveX, moveY) == false)
				{
					if (other->canMove == true)
					{
						box.vx -= boxOther.vx;
						box.vy -= boxOther.vy;
						boxOther.vx = 0;
						boxOther.vy = 0;
					}
				}
		}
	}

}

void ActiveObject::SetActive(float _vX, float _vY)
{
	//chua dinh nghia
}

void ActiveObject::ReceiveDamage(int damage)
{
	//chua dinh nghia
}

bool ActiveObject::IntoScreen(float _x, float _y, GCamera* camera)
{
	/*
	if (posX + width / 2 <= camera->viewport.x || posX - width / 2 >= camera->viewport.x + G_ScreenWidth
		|| posY + height / 2 <= camera->viewport.y || posY - height / 2 >= camera->viewport.y + G_ScreenHeight)
	*/

	
	if (_x <= camera->viewport.x || _x >= camera->viewport.x + G_ScreenWidth
		|| _y <= camera->viewport.y || _y >= camera->viewport.y + G_ScreenHeight)
		return false;
	return true;
	
}