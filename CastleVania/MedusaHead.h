#pragma once
#include "ActiveObject.h"

#define	MEDUSAHEAD_SPEED 0.2f
#define MEDUSAHEAD_DAMAGE 2
#define MEDUSAHEAD_HP 1
#define MEDUSAHEAD_POINT 300


class MedusaHead :
	public ActiveObject
{
public:
	MedusaHead();
	MedusaHead(float _posX, float _posY, int _width, int _height);
	~MedusaHead();

	void MovePath(int deltaTime);
	void Draw(GCamera* camera);
	void Update(int deltaTime);

	//Va cham, chua dinh nghia
	void Collision();
};

