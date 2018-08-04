#include "Whip.h"



Whip::Whip(int _x, int _y, float _vx, float _vy, EnumID id, int _whipRate)
{
	//abc = true;
	vX = _vx;
	vY = _vy;
	damage = 1;
	whipSprite = new WhipSprite(TextureManager::getInstance()->getTexture(EnumID::MorningStar_ID), 0, 2, _whipRate);
}

Whip::Whip()
{
}


Whip::~Whip()
{
}

void Whip::Reset()
{
	whipSprite->Reset();
}

void Whip::Update(int deltaTime)
{
	whipSprite->Update(deltaTime);
}

void Whip::Draw(GCamera *camera)
{
	D3DXVECTOR2 pos = camera->Transform(x, y);
	if (vX > 0)
	{
		whipSprite->DrawFlipX(pos.x, pos.y);
	}
	else
	{
		whipSprite->Draw(pos.x, pos.y);
	}
}

Box Whip::GetBox()
{
	int currentState = whipSprite->GetIndex();
	if (currentState < 0 || currentState > 8)
		return Box(0, 0, 0, 0);
	WhipRect* whipSize = this->whipSprite->getWhipSize().at(currentState);
	return Box(x, y, whipSize->w, whipSize->h);
}

void Whip::UpdateXY(int _x, int _y)
{
	float whipX = 0;
	float whipY = 0;
	int whipState = this->whipSprite->GetIndex();
	x = _x;		//tọa độ x của simon
	y = _y;		//tọa độ y của simon
	if (whipState % 3 == 2)
	{
		whipX = x - 30;
		whipY = y - 30;
	}
	this->x = whipX;
	this->y = whipY;
}

void Whip::UpdateVx(float _vX)
{
	vX = _vX;
}

void Whip::UpdateLevel()
{
	this->whipSprite->LevelUp();
}

bool Whip::GetData()
{
	return false;
}
