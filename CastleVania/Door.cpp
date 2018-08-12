#include "Door.h"



Door::Door()
{
}

Door::Door(float _posX, float _posY, int _width, int _height) :
	GameObject(_posX, _posY, EnumID::Door_ID)
{
	width = _width;
	height = _height;
	sprite = new GSprite(TextureManager::getInstance()->getTexture(EnumID::Door_ID), 0, 3, 1000);
	_timeCount = 0;
	animating = false;
	playedClose = false;
	playedOpen = false;
}

Door::~Door()
{
}

void Door::RenderOpen()
{
	if (!isOpen)
	{
		animating = true;
		if (!playedOpen)
		{
			//SoundManager::GetInst()->PlaySoundEffect(ESoundEffect::ES_Door);
			playedOpen = true;
		}
		_timeCount += 1;
		if (_timeCount <= 40)
		{
			
			if (_timeCount > 10 && _timeCount < 20)
				sprite->SelectIndex(0); // cho nay la thay doi su kien cai cong
										//{ }
			else if (_timeCount >= 20 && _timeCount < 40)
			{
				sprite->SelectIndex(2); // thay doi cai cong
			}
		}
		if (_timeCount == 40)
		{
			_timeCount = 0;
			animating = false;
			isOpen = true;

		}
	}
}

void Door::RenderClose()
{
	if (isOpen)
	{
		animating = true;
		if (!playedClose)
		{
			//SoundManager::GetInst()->PlaySoundEffect(ESoundEffect::ES_Door);
			playedClose = true;
		}
		_timeCount += 1;
		if (_timeCount <= 40)
		{
			animating = true;
			if (_timeCount > 10 && _timeCount < 20)
			{
				sprite->SelectIndex(3);
			} else if (_timeCount >= 20 && _timeCount < 40) {
				sprite->SelectIndex(1);
			} else {
				sprite->SelectIndex(2);
			}

		}
		if (_timeCount == 40)
		{
			_timeCount = 0;
			animating = false;
			isOpen = false;
		}
	}
}

bool Door::isAnimating()
{
	return animating;
}

void Door::Update(int dt)
{
	return;
}

void Door::ResetDoor()
{
	animating = false;
	isOpen = false;
}

void Door::Draw(GCamera* camera, int vX, int stage)
{
	D3DXVECTOR2 center = camera->Transform(x, y);
	if (vX < 0)
	{
		sprite->DrawFlipX(center.x, center.y);
	}
	else
	{
		sprite->Draw(center.x, center.y);
	}
}

