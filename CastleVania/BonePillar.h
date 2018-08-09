#pragma once
#include "Enemy.h"

#include "Fire.h"

class BonePillar :
	public Enemy
{
public:

	list<ActiveObject*> *listFire;
	int reloadTime;
	bool isLeft;

	void UpdateFire(float dt);
	void DrawFire(GCamera* camera);

	void Update(int dt);
	void Draw(GCamera* camera);

	void Collision();


	BonePillar();
	BonePillar(float _x, float _y, bool _isLeft);
	~BonePillar();
};

