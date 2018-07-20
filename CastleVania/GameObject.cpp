
#include "GameObject.h"
#include <d3d9.h>

GameObject::GameObject(void)
{
	posX = 0;
	posY = 0;
	width = 0;
	height = 0;
	canMove = false;
	canBeKilled = true;

	neededPlayerPosition = false;
}


GameObject::GameObject(float _posX, float _posY, EnumID _id)
{
	posX = _posX;
	posY = _posY;
	vX = 0;
	vY = 0;
	id = _id;
	
	hp = 1;
	point = 1;
	type = ObjectType::None;
	canMove = false;
	active = true;
	
	CreateSprite();
	if (sprite != NULL)
	{
		width = sprite->_texture->FrameWidth;
		height = sprite->_texture->FrameHeight;
	}
}

void GameObject::CreateSprite()
{
	
}


void GameObject::Update(int deltaTime)
{
	if (sprite != NULL)
		sprite->Update(deltaTime);
}
void GameObject::Update(int, int, int dt) {

}
void GameObject::Draw(GCamera* camera)
{
	if (sprite != NULL)
	{
		D3DXVECTOR2 center = camera->Transform(posX, posY);
		sprite->Draw(center.x, center.y);
	}
}
void GameObject::ReceiveDamage(int damage)
{
	if (hp > 0) {
		hp -= damage;
	}
	else {
		death = true;
	}
}
void GameObject::Collision(list<GameObject*> obj, int dt)
{
}
void GameObject::Remove()
{
	active = false;
	death = true;
}
Box GameObject::GetBox()
{
	Box result(posX - width / 2, posY + height / 2, width, height);
	return result;
}
void GameObject::ProcessInput(LPDIRECT3DDEVICE9 d3ddv, int t) {}
void GameObject::OnKeyDown(int KeyCode) {}
GameObject::~GameObject(void) {}
void GameObject::SetActive(float x, float y){}
void GameObject::SetActive()
{
	if (!active)
		active = true;
}

/*
void GameObject::Pause() {
	vX = 0;
	vY = 0;
}
*/

ECollisionDirection GameObject::GetCollisionDirect(float normalx, float normaly)
{
	if (normalx == 0 && normaly == 1)
	{
		return ECollisionDirection::Colls_Bot;
	}
	if (normalx == 0 && normaly == -1)
	{
		return ECollisionDirection::Colls_Top;
	}
	if (normalx == 1 && normaly == 0)
	{
		return ECollisionDirection::Colls_Left;
	}
	if (normalx == -1 && normaly == 0)
	{
		return ECollisionDirection::Colls_Right;
	}
	return ECollisionDirection::Colls_None;
}
