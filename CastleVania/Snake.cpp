#include "Snake.h"



Snake::Snake() : ActiveObject()
{
}

Snake::Snake(float _posX, float _posY, float _vX, float _vY, EnumID _id)
	: ActiveObject(_posX, _posY, _vX, _vY, _id)
{
	active = true;
	canBeKilled = true;
	type = ObjectType::Enemy_Type;
}


Snake::~Snake()
{
}

void Snake::Draw(GCamera* camera)
{
	if (sprite == NULL || !active)
		return;
	if (posX + width / 2 <= camera->viewport.x || posX - width / 2 >= camera->viewport.x + G_ScreenWidth)
	{
		active = false;
		return;
	}
	D3DXVECTOR2 center = camera->Transform(posX, posY);
	if (vX > 0)
		sprite->DrawFlipX(center.x, center.y);
	else
		sprite->Draw(center.x, center.y);
}

void Snake::Collision()
{

}
