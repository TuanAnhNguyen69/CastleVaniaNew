#include "WhipSprite.h"


void WhipSprite::Init()
{
	whipSize = vector<WhipRect*>();

	//Add từng size của 9 sprite (gồm 3 level, mỗi level 3 sprite) vào danh sách whipSize
	whipSize.push_back(new WhipRect(137, 18, 16, 48));
	whipSize.push_back(new WhipRect(280, 12, 32, 38));
	whipSize.push_back(new WhipRect(352, 16, 56, 18));
	whipSize.push_back(new WhipRect(136, 86, 16, 48));
	whipSize.push_back(new WhipRect(280, 80, 32, 38));
	whipSize.push_back(new WhipRect(352, 90, 56, 12));
	whipSize.push_back(new WhipRect(136, 154, 16, 48));
	whipSize.push_back(new WhipRect(280, 148, 32, 38));
	whipSize.push_back(new WhipRect(320, 158, 88, 12));
}

WhipSprite::WhipSprite()
{
}

WhipSprite::WhipSprite(const WhipSprite & whip)
{
}


WhipSprite::WhipSprite(GTexture * texture, int start, int end, int timeAnimation)
{
}

WhipSprite::~WhipSprite()
{
}

void WhipSprite::Draw(int x, int y)
{
	if (_index > 8)
		return;
	WhipRect* whipRect = whipSize.at(_index);
	RECT* srect = whipRect->ToRect();

	D3DXVECTOR3 center(0, 0, 0);
	D3DXVECTOR3 position(0, 0, 0);
	position.x = x - whipRect->w / 2;
	position.y = y - whipRect->h / 2;

	G_SpriteHandler->Draw(
		_texture->Texture,
		srect,
		&center,
		&position,
		D3DCOLOR_XRGB(225, 255, 255)
	);
	delete srect;
}

void WhipSprite::LevelUp()
{
	_start = 6;
	_end = 8;
	_index = 6;
}

vector<WhipRect*> WhipSprite::getWhipSize()
{
	return whipSize;
}
