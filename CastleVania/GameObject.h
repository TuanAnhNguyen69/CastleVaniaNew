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
	//cao, rong hit box
	int width;
	int height;
	//huong di chuyen
	float vX, vY;
	ObjectType type;

	bool canMove;
	bool canBeKilled;

	//co dang hoat dong
	bool active;

	//da chet hay chua
	bool death;
	
	//Cac thong so
	EnumID id;
	int hearts;
	int hp;
	int damage;
	int point;
	bool neededPlayerPosition;


	virtual void Update(int dt);
	virtual void Draw(GCamera*);
	virtual void Update(int , int, int dt);

	virtual void ProcessInput(LPDIRECT3DDEVICE9 d3ddv, int t);
	virtual void OnKeyDown(int KeyCode);
	virtual void CreateSprite();
	virtual void SetActive(float x, float y);
	virtual void SetActive();
	
	

	virtual void Collision(list<GameObject*> obj, int dt);
	virtual Box GetBox();
	virtual void ReceiveDamage(int damage);
	ECollisionDirection GetCollisionDirect(float normalx, float normaly);
	virtual void Remove();


	virtual void Pause();
	GameObject(void);
	GameObject(float posX, float posY, EnumID id);
	~GameObject(void);
};

#endif
