#ifndef _GAMEOBJECT_H_
#define _GAMEOBJECT_H_

#include "GSprite.h"
#include "EnumManager.h"
#include "TextureManager.h"
#include "GCamera.h"
#include "SweptAABB.h"
#include <list>
#include "Sound.h"

using namespace std;
class GameObject
{
public:
	
	GSprite* sprite;

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

	//Cac thong so
	EnumID id;
	int hearts;
	int hp;
	int damage;
	int point;
	
	//Dành cho RewardItem
	bool isDrop;


	virtual void Update(int dt);
	virtual void Draw(GCamera*);
	virtual void Update(float _xSimon, float _ySimon, int dt);

	//Tao bien sprite
	virtual void CreateSprite();
	
	//Va cham
	virtual void Collision(list<GameObject*> &obj, int dt);

	//Va chạm với Simon (Chỉ dành cho boomerang)
	virtual void CollSimon(GameObject* simon, int dt);

	//Tra ve kieu va cham
	ECollisionDirection GetCollisionDirect(float normalx, float normaly);

	//Lay thuoc tinh cua Box
	virtual Box GetBox();

	//Lấy vị trí của object
	virtual D3DXVECTOR2 GetPos();

	//Xoa object
	virtual void Remove();


	//Dành cho Enemy
	//Tính damage
	virtual void ReceiveDamage(int _damage);
	
	//Xét hành động của Enemy, dựa vào Simon
	virtual void SetActive(float _xSimon, float _ySimon);


	GameObject(void);
	//GameObject(float _posX, float _posY, int _width, int _height, EnumID id);
	GameObject(float _x, float _y, EnumID id);
	~GameObject(void);
};
#endif
