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
	bool fly;
	MedusaHead();
	MedusaHead(float _x, float _y);
	~MedusaHead();

	void MovePath(int dt);
	void Draw(GCamera* camera);
	void Update(int dt);
	void SetActive(float _x_Simon, float _y_Simon);

	//Va cham, chua dinh nghia
	void Collision();
};

