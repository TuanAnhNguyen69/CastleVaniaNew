#pragma once
#include "ActiveObject.h"

#include "Fire.h"

class BonePillar :
	public ActiveObject
{
public:

	list<ActiveObject*> *listFire;
	int lifeTime;
	bool isLeft;

	void UpdateFire(float deltaTime);
	void DrawFire(GCamera* camera);

	void Update(int deltaTime);
	void Draw(GCamera* camera);

	void Collision();


	BonePillar();
	BonePillar(float _x, float _y, bool _isLeft);
	~BonePillar();
};

