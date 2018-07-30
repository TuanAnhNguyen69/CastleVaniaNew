#include "Snake.h"



Snake::Snake() : ActiveObject()
{
}

Snake::Snake(float _posX, float _posY, int _width, int _height, float _vX, float _vY, EnumID _id)
	: ActiveObject(_posX, _posY, _width, _height, _vX, _vY, _id)
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
	if (x + width <= camera->viewport.x || x >= camera->viewport.x + G_ScreenWidth)
	{
		active = false;
		return;
	}
	D3DXVECTOR2 center = camera->Transform(x, y);
	if (vX > 0)
		sprite->DrawFlipX(center.x, center.y);
	else
		sprite->Draw(center.x, center.y);
}

void Snake::Collision()
{

}
