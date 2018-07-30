#ifndef _GAMEOBJECT_H_
#define _GAMEOBJECT_H_

#include "GSprite.h"
#include "EnumManager.h"
#include "TextureManager.h"
#include "GCamera.h"
#include "SweptAABB.h"
#include <list>
using namespace std;
class GameObject
{
public:
	
	GSprite* sprite;

	//posX, posY -> toa do center
	float posX;
	float posY;

	//toa do left top
	float x;
	float y;

	//cao, rong hit box
	int width;
	int height;

	//huong di chuyen
	float vX;
	float vY;

	//Loai object
	ObjectType type;

	//Co the di chuyen khong
	bool canMove;

	//Co the bi tieu diet / pha huy ko
	bool canBeKilled;

	//co dang hoat dong
	bool active;

	//da chet hay chua
	bool isDeath;

	//Object co phu thuoc vao vi tri cua Simon khong
	bool neededPlayerPosition;
	
	//Cac thong so
	EnumID id;
	int hearts;
	int hp;
	int damage;
	int point;
	


	virtual void Update(int dt);
	virtual void Draw(GCamera*);
	virtual void Update(int , int, int dt);

	virtual void ProcessInput(LPDIRECT3DDEVICE9 d3ddv, int t);
	virtual void OnKeyDown(int KeyCode);

	//Tao bien sprite
	virtual void CreateSprite();

	//Thay doi gia tri bien active
	virtual void SetActive(float x, float y);
	virtual void SetActive();
	
	
	//Va cham
	virtual void Collision(list<GameObject*> obj, int dt);

	//Tra ve kieu va cham
	ECollisionDirection GetCollisionDirect(float normalx, float normaly);

	//Lay thuoc tinh cua Box
	virtual Box GetBox();

	//Nhan damage
	virtual void ReceiveDamage(int damage);

	//Xoa object
	virtual void Remove();


	//virtual void Pause();
	GameObject(void);
	//GameObject(float _posX, float _posY, int _width, int _height, EnumID id);
	GameObject(float _x, float _y, int _width, int _height, EnumID id);
	~GameObject(void);
};

#endif
