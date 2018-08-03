#ifndef _MORNINGSTAR_H_
#define _MORNINGSTAR_H_

#include "GameObject.h"
#include "Medusa.h"
#include <vector>
#include "RewardItem.h"
using namespace std;

class MorningStar :
	public GameObject
{
public:
	MorningStar(void);
	MorningStar(int posX, int posY, int MorningStarRate);
	int level;
	int damage;

	void reset();
	bool isLeft;
	virtual void Draw(GCamera* camera);
	virtual Box GetBox();

	void update(int posX, int posY, int deltaTime);
	void updateDirection(bool);
	void updateLevel();
	bool getdata();
	void Collision(list<GameObject*> &obj, int dt);
	~MorningStar(void);
};

#endif