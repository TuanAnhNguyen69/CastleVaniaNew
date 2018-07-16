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
	//Vi du
	Simon = new GTexture("Resources/player.png", 8, 3, 24);
	SimonDeath = new GTexture("Resources/Playerdeath.png", 1, 1, 1);
	MorningStar = new GTexture("Resources/morningstar.png", 3, 3, 9);
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
	case EnumID::Dagger_ID:
		return Dagger;
	case EnumID::HolyWater_ID:
		return HolyWater;
	case EnumID::StopWatch_ID:
		return StopWatch;

	//Weapon
	case EnumID::ChainWhip_ID:
		return ChainWhip;
	case EnumID::MorningStar_ID:
		return MorningStar;

	//Item
	case EnumID::Item_Axe_ID:
		return Item_Axe;
	case EnumID::Item_Boomerang_ID:
		return Item_Boomerang;
	case EnumID::Item_Dagger_ID:
		return Item_Dagger;
	case EnumID::Item_HolyWater_ID:
		return Item_HolyWater;
	case EnumID::Item_StoWatch_ID:
		return Item_StopWatch;

	case EnumID::Item_ChainWhip:
		return Item_ChainWhip;
	case EnumID::Item_MorningStar:
		return Item_MorningStar;
	
	case EnumID::LargeHeart_ID:
		return LargeHeart;
	case EnumID::SmallHeart_ID:
		return SmallHeart;
	case EnumID::RedMoneyBag_ID:
		return RedMoneyBag;
	case EnumID::WhiteMoneyBag_ID:
		return WhiteMoneyBag;
	case EnumID::PurpleMoneyBag_ID:
		return PurpleMoneyBag;
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