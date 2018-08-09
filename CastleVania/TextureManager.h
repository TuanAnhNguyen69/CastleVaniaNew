#pragma once
#include "GTexture.h"
#include "EnumManager.h"

class TextureManager
{
private:
	//Simon
	GTexture* simon;
	GTexture* deadSimon;

	//Enemy
	GTexture* bat;
	GTexture* spearGuard;
	GTexture* medusaHead;
	GTexture* ghost;
	GTexture* bonePillar;
	GTexture* fire;

	//Boss
	GTexture* dracula;
	GTexture* medusa;
	GTexture* snake;

	//Ground
	GTexture* brick;
	GTexture* testBrick;
	GTexture* stairTop;
	GTexture* stairBot;

	GTexture* breakableBrick;
	GTexture* candle;
	GTexture* movingPlatform;
	GTexture* door;
	GTexture* trap;
	GTexture* transparentSprite;

	//Sub-Weapon
	GTexture* axe;
	GTexture* boomerang;
	GTexture* knife;
	GTexture* holyWater;
	GTexture* stopWatch;
	
	//Weapon
	GTexture* weapon;
	GTexture* chainWhip;
	GTexture* morningStar;

	//Item
	GTexture* item_Axe;
	GTexture* item_Boomerang;
	GTexture* item_Knife;
	GTexture* item_FireBomb;
	GTexture* item_StopWatch;

	GTexture* item_ChainWhip;
	GTexture* item_MorningStar;

	GTexture* trippleShot;
	GTexture* bigHeart;
	GTexture* doubleShot;
	GTexture* smallHeart;
	GTexture* moneyBag400;
	GTexture* moneyBag700;
	GTexture* crown;
	GTexture* cross;
	GTexture* tresureChest;
	GTexture* magicBall;
	GTexture* porkChop;

	//Other
	GTexture* hitEffect;
	GTexture* rewardItem;
	GTexture* hp;
	GTexture* gameScore;


	static TextureManager *single; 

public:
	static TextureManager* getInstance();
	TextureManager(void);
	~TextureManager();
	GTexture* getTexture(EnumID id);
};

