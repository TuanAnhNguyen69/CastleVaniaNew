
#ifndef _EnumManager_H_
#define _EnumManager_H_

static enum EnumSceneState
{
	Scene_Menu,
	State_1,
	Scene_Game,
	Scene_End
};

enum EnumID
{
	None_ID,
	Simon_ID,
	SimonDeath_ID,

	Brick_ID,
	Barrier_ID,
	Candle_ID,
	LargeCandle_ID,

	//enemy
	Zombie_ID,
	MedusaHead_ID,
	Bat_ID,
	SpearGuard_ID,
	BonePillar_ID,
	Ghost_ID,
	VampireBat_ID,
	//Eagle_ID,
	//Skeletons_ID,
	Merman_ID,
	Panther_ID,


	//ground
	MovingPlatform_ID,
	StairUpLeft_ID,
	StairUpRight_ID,
	StairDownLeft_ID,
	StairDownRight_ID,

	DoorLeft_ID,
	DoorRight_ID,
	TeleUp_ID,
	TeleDown_ID,
	OpenDoor_ID,
	Trap_ID,
	CastleGate_ID,
	BreakableBrick_ID,

	//boss
	Medusa_ID,
	Count_Dracula_ID,
	Snake_ID,

	//other
	Water_ID,
	Fire_ID,
	HitEffect_ID,
	HP_ID,
	Score_ID,

	//Item
	VampireKiller_ID,
	MorningStar_ID,
	ChainWhip_ID,
	SmallHeart_ID,
	BigHeart_ID,
	WhiteMoneyBag_ID,
	BlueMoneyBag_ID,
	RedMoneyBag_ID,
	ExtraMoneyBag_ID,
	Roast_ID,
	Rosary_ID,
	InvisibilityPotion_ID,
	Crown_ID,
	MoauiHead_ID,
	TreasureChest_ID,
	DoubleShot_ID,
	TripleShot_ID,
	SpiritBall_ID,
	OneUp_ID,
	Cross_ID,

	RewardItem_ID,

	Item_Axe_ID,
	Item_Boomerang_ID,
	Item_Knife_ID,
	Item_HolyWater_ID,
	Item_StopWatch_ID,

	Item_ChainWhip,
	Item_MorningStar,


	//weapon
	Axe_ID,
	Boomerang_ID,
	Knife_ID,
	HolyWater_ID,
	StopWatch_ID,

	Weapon_ID,
};
enum EStairType
{
	UpRight,
	UpLeft,
	DownRight,
	DownLeft,
	None_Kind
};

enum Enum_RewardItem_ID
{
	RI_Crown,
	RI_Cross,
	RI_Roast,
	RI_RedBagMoney,
	RI_WhiteBagMoney,
	RI_BlueBagMoney,
	RI_ExtraBagMoney,
	RI_SmallHeart,
	RI_BigHeart,
};

enum ObjectType {
	None,
	Item,
	Enemy_Type,
	Other
};
enum Action
{
	Stand,
	Run_Right,
	Run_Left,
	Jump,
	Fight,
	Sit,
	Fall,
	IntoCastle
};

enum SimonAction
{
	SimonStand,
	SimonMove,
	SimonUpStair,
	SimonDownStair,
	SimonSit,
	SimonJump,
	SimonThrow,
	SimonAttack,
	SimonHit,
	SimonDie,
	SimonUpgrade

};

enum ECollisionDirection
{
	Colls_None,
	Colls_Left,
	Colls_Right,
	Colls_Bot,
	Colls_Top
};


//enum EMoveDirection
//{
//	MoveUp,
//	MoveDown,
//	MoveRight,
//	MoveLeft,
//	None
//};

enum EDoorDirection
{
	TeleUp,
	TeleDown,
	DoorRight,
	DoorLeft,
	NoneDoor
};
enum ECameraState
{
	Update_Camera,
	NoUpdate_Camera
};

enum EFleamanState {
	WAIT = 0,
	MOVE = 1
};
#endif