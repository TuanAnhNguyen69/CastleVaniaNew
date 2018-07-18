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
	Simon = new GTexture("Resources/sprites/Simon/Simon.png", 8, 3, 24);
	SimonDeath = new GTexture("Resource/sprites/Simon/Simon_Death.png", 1, 1, 1);
	Weapon = new GTexture("Resource/sprites/Weapon/Weapon.png", 3, 3, 9);

	//Enemy
	Zombie = new GTexture("Resource/sprites/Enemies/Zombie.png", 2, 1, 2);
	Bat = new GTexture("Resource/sprites/Enemies/Bat.png", 4, 1, 4);
	BonePillar = new GTexture("Resource/sprites/Enemies/Bone_Pillar.png", 1, 1, 1);
	Merman = new GTexture("Resource/sprites/Enemies/Merman.png", 3, 1, 3);
	MedusaHead = new GTexture("Resource/sprites/Enemies/Medusa_Head.png", 2, 1, 2);
	SpearGuard = new GTexture("Resource/sprites/Enemies/Spear_Guard.png", 4, 1, 4);
	Panther = new GTexture("Resource/sprites/Enemies/Panther.png", 4, 1, 4);
	Fire = new GTexture("Resource/sprites/Enemies/Fire.png", 1, 1, 1);
	Ghost = new GTexture("Resource/sprites/Enemies/Ghost.png", 2, 1, 2);

	//Boss
		//Ban lai
	Medusa = new GTexture("Resource/sprites/Bosses/Medusa.png", 5, 1, 5);

	VampireBat = new GTexture("Resource/sprites/Bosses/Vampire_Bat.png", 3, 1, 3);

	//Ground
	Brick = new GTexture("Resource/sprites/Ground/Brick.png", 1, 1, 1);

		//Xem lai
	BreakableBrick = new GTexture("Resource/sprites/Ground/Brick.png", 1, 1, 1);

	Candle = new GTexture("Resource/sprites/Ground/1.png", 2, 1, 2);
	LargeCandle = new GTexture("Resource/sprites/Ground/0.png", 2, 1, 2);
	MovingPlatform = new GTexture("Resource/sprites/Ground/9.png", 1, 1, 1);
	OpenDoor = new GTexture("Resource/sprites/Ground/Gate_new.png", 2, 1, 2);
	Trap = new GTexture("Resource/sprites/Ground/7_rope.png", 2, 1, 2);

	//Sub-Weapon
	Axe = new GTexture("Resource/sprites/Sub_Weapons/Axe.png", 4, 1, 4);
	Boomerang = new GTexture("Resource/sprites/Sub_Weapons/Boomerang.png", 3, 1, 3);
	Knife = new GTexture("Resource/sprites/Sub_Weapons/Knife.png", 1, 1, 1);
	HolyWater = new GTexture("Resource/sprites/Sub_Weapons/HolyWater.png", 3, 1, 3);
	//StopWatch khong co animation su dung

	//Weapon
	Weapon = new GTexture("Resource/sprites/Weapon/Weapon.png", 3, 3, 9);

	//Item
	Item_Axe = new GTexture("Resource/sprites/Sub_Weapons/Axe_Item.png", 1, 1, 1);
	Item_Boomerang = new GTexture("Resource/sprites/Sub_Weapons/Boomerang_Item.png", 1, 1, 1);
	Item_Knife = new GTexture("Resource/sprites/Sub_Weapons/Knife_Item.png", 1, 1, 1);
	Item_HolyWater = new GTexture("Resource/sprites/Sub_Weapons/HolyWater_Item.png", 1, 1, 1);
	Item_StopWatch = new GTexture("Resource/sprites/Sub_Weapons/StopWatch_Item.png", 1, 1, 1);

	Item_MorningStar = new GTexture("Resource/sprites/Items/MorningStar.png", 1, 1, 1);

	SmallHeart = new GTexture("Resource/sprites/Items/Small_Heart.png", 1, 1, 1);
	BigHeart = new GTexture("Resource/sprites/Items/Big_Heart.png", 1, 1, 1);
	RedMoneyBag = new GTexture("Resource/sprites/Items/Red_Money_Bag.png", 1, 1, 1);
	WhiteMoneyBag = new GTexture("Resource/sprites/Items/White_Money_Bag.png", 1, 1, 1);
	BlueMoneyBag = new GTexture("Resource/sprites/Items/Blue_Money_Bag.png", 1, 1, 1);
	ExtraMoneyBag = new GTexture("Resource/sprites/Items/Extra_Money_Bag.png", 3, 1, 3);
	Roast = new GTexture("Resource/sprites/Items/Roast.png", 1, 1, 1);
	Cross = new GTexture("Resource/sprites/Items/Cross.png", 1, 1, 1);
	SpiritBall = new GTexture("Resource/sprites/Items/SpiritBall.png", 1, 1, 1);
	Crown = new GTexture("Resource/sprites/Items/Crown.png", 4, 1, 4);

	//Other
	HitEffect = new GTexture("Resource/sprites/Effect/0.png", 1, 1, 1);
	Water = new GTexture("Resource/sprites/Effect/1.png", 1, 1, 1);
	
	//HP
	//Score

}

GTexture* TextureManager::getTexture(EnumID id)
{
	switch (id)
	{
	//Simon
	case EnumID::Simon_ID :
		return Simon;
	case EnumID::SimonDeath_ID:
		return SimonDeath;

	//Enemy
	case EnumID::Zombie_ID:
		return Zombie;
	case EnumID::Bat_ID:
		return Bat;
	case EnumID::BonePillar_ID:
		return BonePillar;
	case EnumID::Merman_ID:
		return Merman;
	case EnumID::MedusaHead_ID:
		return MedusaHead;
	case EnumID::SpearGuard_ID:
		return SpearGuard;
	case EnumID::Panther_ID:
		return Panther;
	case EnumID::Fire_ID:
		return Fire;
	case EnumID::Ghost_ID:
		return Ghost;

	//Boss
	case EnumID::VampireBat_ID:
		return VampireBat;
	case EnumID::Medusa_ID:
		return Medusa;

	//Ground
	case EnumID::Brick_ID:
		return Brick;
	case EnumID::BreakableBrick_ID:
		return BreakableBrick;
	case EnumID::Candle_ID:
		return Candle;
	case EnumID::MovingPlatform_ID:
		return MovingPlatform;
	case EnumID::OpenDoor_ID:
		return OpenDoor;
	case EnumID::Trap_ID:
		return Trap;

	//Sub-Weapon
	case EnumID::Axe_ID:
		return Axe;
	case EnumID::Boomerang_ID:
		return Boomerang;
	case EnumID::Knife_ID:
		return Knife;
	case EnumID::HolyWater_ID:
		return HolyWater;
	case EnumID::StopWatch_ID:
		return StopWatch;

	//Weapon
	case EnumID::Weapon_ID:
		return Weapon;
	case EnumID::ChainWhip_ID:
		return ChainWhip;
	case EnumID::MorningStar_ID:
		return MorningStar;

	//Item
	case EnumID::Item_Axe_ID:
		return Item_Axe;
	case EnumID::Item_Boomerang_ID:
		return Item_Boomerang;
	case EnumID::Item_Knife_ID:
		return Item_Knife;
	case EnumID::Item_HolyWater_ID:
		return Item_HolyWater;
	case EnumID::Item_StoWatch_ID:
		return Item_StopWatch;

	case EnumID::Item_ChainWhip:
		return Item_ChainWhip;
	case EnumID::Item_MorningStar:
		return Item_MorningStar;
	
	case EnumID::BigHeart_ID:
		return BigHeart;
	case EnumID::SmallHeart_ID:
		return SmallHeart;
	case EnumID::RedMoneyBag_ID:
		return RedMoneyBag;
	case EnumID::WhiteMoneyBag_ID:
		return WhiteMoneyBag;
	case EnumID::BlueMoneyBag_ID:
		return BlueMoneyBag;
	case EnumID::ExtraMonneyBag_ID:
		return ExtraMoneyBag;
	case EnumID::Crown_ID:
		return Crown;
	case EnumID::Cross_ID:
		return Cross;
	case EnumID::SpiritBall_ID:
		return SpiritBall;
	case EnumID::Roast_ID:
		return Roast;

	//Other
	case EnumID::HitEffect_ID:
		return HitEffect;
	case EnumID::Water_ID:
		return Water;
	case EnumID::Barrier_ID:
		return Barrier;
	case EnumID::HP_ID:
		return HP;
	case EnumID::Score_ID:
		return Score;

	}
}