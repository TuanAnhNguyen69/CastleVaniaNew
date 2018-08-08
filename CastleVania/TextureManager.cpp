#include "TextureManager.h"
#include <string>
#include <sstream>
#include <windows.h>
#include <iostream>
#include <malloc.h>

using namespace std;

TextureManager* TextureManager::single = NULL;


TextureManager::~TextureManager()
{
}

TextureManager* TextureManager::getInstance()
{
	if (single == NULL)
		single = new TextureManager();
	return single;
}

TextureManager::TextureManager(void)
{
	//Simon
	simon = new GTexture("Resource/sprites/Simon/Simon.png", 8, 3, 24);
	deadSimon = new GTexture("Resource/sprites/Simon/Simon_Death.png", 1, 1, 1);

	//Enemy
	bat = new GTexture("Resource/sprites/Enemies/Bat.png", 4, 1, 4);
	bonePillar = new GTexture("Resource/sprites/Enemies/Bone_Pillar.png", 1, 1, 1);
	medusaHead = new GTexture("Resource/sprites/Enemies/Medusa_Head.png", 2, 1, 2);
	spearGuard = new GTexture("Resource/sprites/Enemies/Spear_Guard.png", 4, 1, 4);
	fire = new GTexture("Resource/sprites/Enemies/Fire.png", 1, 1, 1);
	ghost = new GTexture("Resource/sprites/Enemies/Ghost.png", 2, 1, 2);

	//Boss
		//Ban lai
	medusa = new GTexture("Resource/sprites/Bosses/medusa.png", 5, 1, 5);

	//dracula = new GTexture("Resource/sprites/Bosses/Vampire_Bat.png", 3, 1, 3);

	snake = new GTexture("Resource/sprites/Bosses/Snake.png", 2, 1, 2);

	//Ground
	brick = new GTexture("Resource/sprites/Ground/NULL.png", 1, 1, 1);
	testBrick = new GTexture("Resource/sprites/Ground/13.png", 3, 1, 3);
	stairTop = new GTexture("Resource/sprites/Ground/stairTop.png", 1, 1, 1);
	stairBot = new GTexture("Resource/sprites/Ground/stairBot.png", 1, 1, 1);
	transparentSprite = new GTexture("Resource/sprites/Ground/NULL.png", 1, 1, 1);
		//Xem lai
	breakableBrick = new GTexture("Resource/sprites/Ground/NULL.png", 1, 1, 1);

	candle = new GTexture("Resource/sprites/Ground/candle.png", 2, 1, 2);
	movingPlatform = new GTexture("Resource/sprites/Ground/movingPlatform.png", 1, 1, 1);
	door = new GTexture("Resource/sprites/Ground/Door.png", 4, 1, 4);
	trap = new GTexture("Resource/sprites/Ground/7_rope.png", 2, 1, 2);

	//Sub-Weapon
	axe = new GTexture("Resource/sprites/Sub_Weapons/Axe.png", 4, 1, 4);
	boomerang = new GTexture("Resource/sprites/Sub_Weapons/Boomerang.png", 3, 1, 3);
	knife = new GTexture("Resource/sprites/Sub_Weapons/Knife.png", 1, 1, 1);
	holyWater = new GTexture("Resource/sprites/Sub_Weapons/HolyWater.png", 3, 1, 3);
	//StopWatch khong co animation su dung

	//Weapon
	weapon = new GTexture("Resource/sprites/Weapon/Weapon.png", 3, 3, 9);
	morningStar = new GTexture("Resource/sprites/Weapon/whip.png", 3, 6, 18);

	//Item
	item_Axe = new GTexture("Resource/sprites/Sub_Weapons/Axe_Item.png", 1, 1, 1);
	item_Boomerang = new GTexture("Resource/sprites/Sub_Weapons/Boomerang_Item.png", 1, 1, 1);
	item_Knife = new GTexture("Resource/sprites/Sub_Weapons/Knife.png", 1, 1, 1);
	item_FireBomb = new GTexture("Resource/sprites/Sub_Weapons/HolyWater_Item.png", 1, 1, 1);
	item_StopWatch = new GTexture("Resource/sprites/Sub_Weapons/StopWatch.png", 1, 1, 1);
	item_MorningStar = new GTexture("Resource/sprites/Items/MorningStar.png", 1, 1, 1);
	smallHeart = new GTexture("Resource/sprites/Items/Small_Heart.png", 1, 1, 1);
	bigHeart = new GTexture("Resource/sprites/Items/Big_Heart.png", 1, 1, 1);
	moneyBag400 = new GTexture("Resource/sprites/Items/Red_Money_Bag.png", 1, 1, 1);
	moneyBag700 = new GTexture("Resource/sprites/Items/Blue_Money_Bag.png", 1, 1, 1);
	porkChop = new GTexture("Resource/sprites/Items/Roast.png", 1, 1, 1);
	cross = new GTexture("Resource/sprites/Items/Cross.png", 1, 1, 1);
	magicBall = new GTexture("Resource/sprites/Items/SpiritBall.png", 1, 1, 1);
	crown = new GTexture("Resource/sprites/Items/Crown.png", 4, 1, 4); 
	doubleShot = new GTexture("Resource/sprites/Items/DoubleShot.png", 1, 1, 1);
	trippleShot = new GTexture("Resource/sprites/Items/TrippleShot.png", 1, 1, 1);
	tresureChest = new GTexture("Resource/sprites/Items/treasure.png", 1, 1, 1);



	//Other
	hitEffect = new GTexture("Resource/sprites/Effect/0.png", 1, 1, 1);
	
	//HP
	//Score

	gameScore = new GTexture("Resource/sprites/UI/blackboard.png", 1, 1, 1);
	hp = new GTexture("Resource/sprites/UI/heal.png", 3, 1, 3);

}

GTexture* TextureManager::getTexture(EnumID id)
{
	switch (id)
	{
	//Simon
	case EnumID::Simon_ID :
		return simon;
	case EnumID::SimonDeath_ID:
		return deadSimon;

	//Enemy
	case EnumID::Bat_ID:
		return bat;
	case EnumID::BonePillar_ID:
		return bonePillar;
	case EnumID::MedusaHead_ID:
		return medusaHead;
	case EnumID::SpearGuard_ID:
		return spearGuard;
	case EnumID::Fire_ID:
		return fire;
	case EnumID::Ghost_ID:
		return ghost;

	//Boss
	case EnumID::Count_Dracula_ID:
		return dracula;
	case EnumID::Medusa_ID:
		return medusa;
	case EnumID::Snake_ID:
		return snake;

	//Ground
	case EnumID::Brick_ID:
		return testBrick;
	case EnumID::Breakable_ID:
		return transparentSprite;
	case EnumID::Candle_ID:
		return candle;
	case EnumID::MovingPlatform_ID:
		return movingPlatform;
	case EnumID::Trap_ID:
		return trap;
	case EnumID::Door_ID:
		return door;
	case EnumID::StairLeft_ID:
	case EnumID::StairRight_ID:
		return transparentSprite;
	case EnumID::StairTopLeft_ID:
	case EnumID::StairTopRight_ID:
		return stairTop;
	case EnumID::StairBotLeft_ID:
	case EnumID::StairBotRight_ID:
		return stairBot;
	//Sub-Weapon
	case EnumID::Axe_Weapon_ID:
		return axe;
	case EnumID::Boomerang_Weapon_ID:
		return boomerang;
	case EnumID::Knife_Weapon_ID:
		return knife;
	case EnumID::HolyWater_Weapon_ID:
		return holyWater;
	case EnumID::StopWatch_Weapon_ID:
		return stopWatch;

	////Weapon
	//case EnumID::Weapon_ID:
	//	return Weapon;
	//case EnumID::ChainWhip_ID:
	//	return ChainWhip;
	case EnumID::MorningStar_Weapon_ID:
		return morningStar;
	//Item
	case EnumID::Axe_ID:
		return item_Axe;
	case EnumID::Boomerang_ID:
		return item_Boomerang;
	case EnumID::Knife_ID:
		return item_Knife;
	case EnumID::HolyWater_ID:
		return item_FireBomb;
	case EnumID::StopWatch_ID:
		return item_StopWatch;
	case EnumID::MorningStar_ID:
		return item_MorningStar;
	case EnumID::BigHeart_ID:
		return bigHeart;
	case EnumID::SmallHeart_ID:
		return smallHeart;
	case EnumID::MoneyBag400_ID:
		return moneyBag700;
	case EnumID::MoneyBag700_ID:
		return moneyBag700;
	case EnumID::Crown_ID:
		return crown;
	case EnumID::Cross_ID:
		return cross;
	case EnumID::SpiritBall_ID:
		return magicBall;
	case EnumID::PorkChop_ID:
		return porkChop;
	case EnumID::DoubleShot_ID:
		return doubleShot;
	case EnumID::TripleShot_ID:
		return trippleShot;
	case EnumID::TreasureChest_ID:
		return tresureChest;

	//Other
	/*case EnumID::HitEffect_ID:
		return HitEffect;
	case EnumID::Water_ID:
		return Water;
	case EnumID::Barrier_ID:
		return Barrier;*/
	case EnumID::HP_ID:
		return hp;
	case EnumID::GameUI_ID:
		return gameScore;

	}
}