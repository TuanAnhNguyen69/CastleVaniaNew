#pragma once
#include "GSprite.h"
#include "WhipRect.h"
#include "GTexture.h"
#include <vector>

using namespace std;

class WhipSprite :
	public GSprite
{
protected:
	vector<WhipRect*> whipSize;
	int level;
	void Init();
public:
	WhipSprite();
	WhipSprite(const WhipSprite &whip);
	WhipSprite(GTexture* texture, int start, int end, int timeAnimation);
	~WhipSprite();
	void Draw(int x, int y);
	void LevelUp();
	vector<WhipRect*> getWhipSize();
};

