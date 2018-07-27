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
#define GRAVITATIONAL 0.005f			//gia toc trong truong

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
	GSprite* simonAttack;
	GSprite* simonSit;
	GSprite* simonDeath;
	GSprite* simonKnockBack;

	//Da chet
	bool isDie;

	//Dang nhay
	bool isJump;

	//Dang dung yen
	bool isStop;

	//Dang ngoi
	bool isSit;

	bool isAttack;

	//Bat tu tam thoi
	bool immortal;

	//Bien enum cac loai hanh dong
	Action action;

	//Vx cuoi cung truoc khi dung lai
	float vLast;

	//Gia toc trong truong
	float g;

public:
	Simon();
	~Simon();

	virtual void Draw(GCamera* camera);
	virtual void Update(int deltaTime);
	virtual void Collision(list<GameObject*> &obj, float dt);
	Simon(int _posX, int _posY);

	//di chuyen
	void RunLeft();
	void RunRight();
	void Sit();
	void Stop();
	void Jump();
	void Attack();
	void OnAttack(int deltaTime);


	//Tu dong di chuyen khi di vao cong
	bool AutoMove(int &rangeMove, int deltaTime);

	Box GetBox();

	//Xu ly dung tren nen dat
	void StandGround(list<GameObject*> &obj, float dt);
	
};


