#pragma once
#include "ActiveObject.h"
#include "MorningStar.h"
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
#define SPEED_Y 0.4f
#define MAX_HEIGHT 70.0f
#define GRAVITATIONAL 0.005f			//gia toc trong truong

#define MAX_HEIGHT_KNOCKBACK 32.0f
#define MAX_WIDTH_KNOCKBACK 38.0f

#define AUTO_MOVE_RANGE 5

class Simon :
	public ActiveObject
{
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

	float y0;

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

	//Dung tren brick
	bool isOnBrick;

	bool isLeft;

	//Bien enum cac loai hanh dong
	Action action;

	//Vx cuoi cung truoc khi dung lai
	float vLast;

	//Gia toc trong truong
	float g;

public:
	Simon();
	~Simon();

	int score;
	int live;
	int weaponCount;
	EnumID weaponID;
	MorningStar* morningStar;
	virtual void Draw(GCamera* camera);
	virtual void Update(int deltaTime);
	virtual void Collision(list<GameObject*> &obj, float dt);
	//Simon(int _posX, int _posY, int _width, int _height);
	Simon(int _x, int _y);

	//di chuyen
	void RunLeft();
	void RunRight();
	void Sit();
	void Stop();
	void Jump();
	void Attack();
	void OnAttack(int deltaTime);

	//Stair
	GameObject* stair;		//đối tượng stair đang xét

	bool colBottomStair;	//có lên cầu thang không
	bool onStair;			//có ở trên stair không
	bool upStair;			//có đi lên stair không
	bool downStair;			//có đi xuống stair không
	bool colStair;			//có chạm vào 1 trong 2 đầu cầu thang không
	bool standOnStair;		//có đứng trên cầu thang không
	bool outStair;			//có ra ngoài cầu thang không
	float rangeStair;		//khoảng các từ simon tới stair
	int timeOnStair;		//thời gian đi 1 bậc
	EStairType stairType;	//loại stair

	void UpStair();
	void DownStair();
	bool OnStair();
	void OutStair();
	void ResetStair();
	void UpdateStair(int deltaTime);
	void SetUpStair();
	void SetDownStair();

	GSprite *simonOnStair;
	GSprite *simonAttackUpStair;
	GSprite *simonAttackDownStair;

	//Tu dong di chuyen khi di vao cong
	bool AutoMove(int &rangeMove, int deltaTime);

	Box GetBox();

	//Xu ly dung tren nen dat
	void StandGround(ECollisionDirection direction, float dt);

	void StandBrick(Box other, int dt, ECollisionDirection colDirection, float colTime);
	void TakeOnStairs(GameObject *other, int dt);
};


