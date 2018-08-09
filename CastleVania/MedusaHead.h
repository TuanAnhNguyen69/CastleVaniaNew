#pragma once
#include "Enemy.h"

#define	MEDUSAHEAD_SPEED 0.2f
#define MEDUSAHEAD_DAMAGE 2
#define MEDUSAHEAD_HP 1
#define MEDUSAHEAD_POINT 300


class MedusaHead :
	public Enemy
{
public:
	MedusaHead();
	MedusaHead(float _x, float _y);
	~MedusaHead();

	void MovePath(int dt);
	void Draw(GCamera* camera);
	void Update(int dt);

	//Va cham, chua dinh nghia
	void Collision();
};

