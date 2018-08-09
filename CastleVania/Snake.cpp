#include "Snake.h"



Snake::Snake() : Enemy()
{
	active = true;
}

Snake::Snake(float _x, float _y, float _direction)
	: Enemy(_x, _y, 0, 0, EnumID::Snake_ID)
{
	hp = 1;
	damage = 1;

	lifeTime = 0;
	active = true;
	canBeKilled = true;
	damage = 4;
	type = ObjectType::Enemy_Type;
	if (_direction > 0)
		vX = SNAKE_SPEED;
	else
		vX = -SNAKE_SPEED;

	vY = 0.5;
	sprite = new GSprite(TextureManager::getInstance()->getTexture(id),0, 1, 100);
}


Snake::~Snake()
{
}

void Snake::Draw(GCamera* camera)
{
	if(sprite == NULL || !active)
		return;
	if (x <= camera->viewport.x || x >= camera->viewport.x + G_ScreenWidth)
	{
		active = false;
		return;
	}
	D3DXVECTOR2 pos = camera->Transform(x, y);
	if (vX > 0)
		sprite->DrawFlipX(pos.x, pos.y);
	else
		sprite->Draw(pos.x, pos.y);
}

void Snake::Update(int dt)
{
	lifeTime += dt;
	x += vX * dt;
	y -= vY * dt;
	if (lifeTime >= 900)
		active = false;
}


void Snake::Collision(list<GameObject*> &obj, int dt)
{
}
