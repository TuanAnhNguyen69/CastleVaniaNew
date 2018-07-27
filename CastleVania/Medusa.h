#pragma once
#include "ActiveObject.h"
#include "Snake.h"
#include <vector>

#define MEDUSA_FIGHT_STATE 20
#define MEDUSA_SLEEP_STATE 10
#define MEDUSA_STOP_STATE 2
#define MEDUSA_SPEED 0.3f
#define SNAKE_SPEED 0.3f
#define MEDUSA_DIE_RATE 10
#define DEAD_TIME 1500
#define PI 3.14f
#define T 1000
#define A 20
#define Sleeping_RightCameraATE 1

enum EnumMedusaState
{
	stSleeping,
	stStop,
	stMoving,
	stDead,
	stRemove
};

class Medusa :
	public ActiveObject
{
protected:
	GSprite * sleepSprite;
	GSprite* fightSprite;
	GSprite* deadSprite;

	vector<D3DXVECTOR2*> listStopPos;				//Cac vi tri ma boss se di chuyen toi
	D3DXVECTOR2* nextStopPos;						//Vi tri tiep theo
	DWORD localTime;
	list<ActiveObject*> *listSnake;

	D3DXVECTOR2* _routerInfo;
	int _previousStopPos;
	int _currentStopPos;

	EnumMedusaState state;
	D3DXVECTOR2* simonPos;
	float deltaPhi;
	float posY0;

	void Initialize();
	void Stoping(int deltaTime_);
	void Moving(int deltaTime_);
	void Deading(int deltaTime_);

	bool LeaveStopPos(D3DXVECTOR2 boss_, D3DXVECTOR2 _nextStopPos);
	void DrawSnakes(GCamera* camera_);
	void UpdateSnakes(int deltaTime_);

public:
	bool isGetUp;


	Medusa();
	Medusa(float posX, float posY, int _width, int _height);
	~Medusa();

	virtual void Update(int deltaTime_);
	void Update(int deltaTime_, D3DXVECTOR2* playerPos_);
	virtual void Draw(GCamera* camera_);
	virtual void Collision();
	//virtual void Collision(list<GameObject*> obj, int dt);
	void GetUp();
	void setDead();
	void ReceiveDamage(int damagePoint);
	bool StateCancel();
	int GetHp();
};

