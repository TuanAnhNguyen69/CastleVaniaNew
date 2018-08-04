#pragma once
#include "GameObject.h"
#include "WhipSprite.h"
#include <vector>
#include "RewardItem.h"
using namespace std;

class Whip :
	public GameObject
{
public:
	WhipSprite* whipSprite;
	Whip(int _x, int _y, float _vX, float _vY, EnumID id, int _whipRate);
	Whip();
	~Whip();

	void Reset();
	virtual void Update(int deltaTime);
	virtual void Draw(GCamera*);
	virtual Box GetBox();

	void UpdateXY(int _x, int _y);
	void UpdateVx(float _vX);
	void UpdateLevel();
	bool GetData();

};

