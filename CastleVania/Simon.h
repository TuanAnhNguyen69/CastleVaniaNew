#pragma once
#include "ActiveObject.h"
/*
#define AX_GO 0.0004
#define VX_GO 0.18
#define VY_JUMP -0.43
#define TIME_INDEX_CHANGE 0.3
#define WEAPON_POSX 16
#define WEAPON_POSY 8
#define WEAPON_BASIC 28
#define WEAPON_UPGRADE 44
#define WEAPON_HEIGHT 8
#define SIMON_HEIGHT 32
*/
#define SIMON_FIGHT_RATE 20
#define SIMON_RATE 10
#define HURT_STATE 25

#define SPEED_X 0.3f
#define SPEED_Y 0.0f
#define SPEED_FALL -0.6f
#define MAX_HEIGHT 70.0f
#define GIATOC 4.0f

#define MAX_HEIGHT_KNOCKBACK 32.0f
#define MAX_WIDTH_KNOCKBACK 38.0f

#define AUTO_MOVE_RANGE 5

class Simon :
	public ActiveObject
{
private:
	static Simon* instance;
protected:
	/*
	GameTime * delayIndexChange;
	int _curSimonAction;
	bool isBlink;	 // thoi gian nhap nhay
	bool _isDownkJump; // có thả phím nhảy // có nhấn phím nhảy
	bool _isDownkSit;
	bool _isGoingUp;
	bool _isGoingDown;
	bool _isColl;
	bool _typeUp, _typeDown; //lên cấp, xuống cấp  
	bool _kLeft, _kRight, _kJump, _kUp, _kDown, _kAttack;
	bool _isUpJumpKey; //
	bool _isDownAtkKey; // có thả, nhấn phím tấn công
	bool isAttacking;
	void setSimonAction(SimonAction action); // thiết lập hành động
	*/

	//Key control
	bool _kLeft, _kRight, _kJump, _kUp, _kDown, _kAttack;
	bool _isDownkJump; // có thả phím nhảy // có nhấn phím nhảy

	//Sprite
	GSprite* simonJum;
	GSprite* simonFight;
	GSprite* simonSit;
	GSprite* simonDeath;
	GSprite* simonKnockBack;

	bool isDie;
	bool isJump;
	bool isStop;
	bool isSit;
	bool immortal;

	Action action;
	float vLast;
	float giatoc;

public:
	Simon();
	~Simon();

	virtual void Draw(GCamera* camera);
	virtual void Update(int deltaTime);
	virtual void Collision(list<GameObject*> &obj, float dt);
	Simon(int _posX, int _posY, int _width, int _height);

	void RunLeft();
	void RunRight();
	void Sit();
	void Stop();

	bool AutoMove(int &rangeMove, int deltaTime);

	Box GetBox();
	void Jump();
	void ChangeAction();

	void StandGround(list<GameObject*> &obj, float dt);
	
};


