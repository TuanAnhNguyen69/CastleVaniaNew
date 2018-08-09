#ifndef _MORNINGSTAR_H_
#define _MORNINGSTAR_H_

#include "GameObject.h"
#include <vector>
#include "RewardItem.h"
#include "Enemy.h"
using namespace std;

class MorningStar :
	public GameObject
{
public:
	MorningStar(void);
	MorningStar(int posX, int posY, int MorningStarRate);
	int level;
	int damage;

	GSprite* lv1;
	GSprite* lv2;
	GSprite* lv3;

	int deltaTime;


	void resetLevel();
	void resetSprite();
	bool isLeft;
	virtual void Draw(GCamera* camera);
	virtual Box GetBox();

	void update(int posX, int posY, int dt);
	void updateDirection(bool);
	void UpdateLevel();
	bool getdata();
	void Collision(list<GameObject*> &obj, int dt);
	~MorningStar(void);
};

#endif