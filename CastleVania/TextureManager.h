#pragma once
#include "GTexture.h"
#include "EnumManager.h"

class TextureManager
{
private:
	//Simon
	GTexture* Simon;
	GTexture* SimonDeath;

	//Enemy
	GTexture* Zombie;
	GTexture* Bat;
	GTexture* Panther;
	GTexture* Merman;
	GTexture* SpearGuard;
	GTexture* MedusaHead;
	GTexture* Ghost;
	GTexture* BonePillar;
	GTexture* Fire;

	//Boss
	GTexture* VampireBat;
	GTexture* Medusa;
	GTexture* Snake;

	//Ground
	GTexture* Brick;
	GTexture* BreakableBrick;
	GTexture* Candle;
	GTexture* LargeCandle;
	GTexture* MovingPlatform;
	GTexture* OpenDoor;
	GTexture* Trap;

	//Sub-Weapon
	GTexture* Axe;
	GTexture* Boomerang;
	GTexture* Knife;
	GTexture* HolyWater;
	GTexture* StopWatch;
	
	//Weapon
	GTexture* Weapon;
	GTexture* ChainWhip;
	GTexture* MorningStar;

	//Item
	GTexture* Item_Axe;
	GTexture* Item_Boomerang;
	GTexture* Item_Knife;
	GTexture* Item_HolyWater;
	GTexture* Item_StopWatch;

	GTexture* Item_ChainWhip;
	GTexture* Item_MorningStar;

	GTexture* BigHeart;
	GTexture* SmallHeart;
	GTexture* RedMoneyBag;
	GTexture* WhiteMoneyBag;
	GTexture* BlueMoneyBag;
	GTexture* ExtraMoneyBag;
	GTexture* Crown;
	GTexture* Cross;
	GTexture* SpiritBall;
	GTexture* Roast;

	//Other
	GTexture* HitEffect;
	GTexture* Water;
	GTexture* Barrier;
	GTexture* BgMenu;
	GTexture* Score;
	GTexture* HP;
	GTexture* RewardItem;

	static TextureManager *single;
	



public:
	static TextureManager* getInstance();
	TextureManager(void);
	~TextureManager();
	GTexture* getTexture(EnumID id);
};

