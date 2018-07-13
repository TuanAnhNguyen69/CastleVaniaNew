
#ifndef _EnumManager_H_
#define _EnumManager_H_

static enum ESceneState
{
	Scene_Menu,
	Scene_Game,
	Scene_End
} EnumSceneState;

enum EnumID
{
	None_ID,
	Player_ID,
	PlayerDeath_ID,

	Brick_ID,
	Barrier_ID,
	Candle_ID,
	LargeCandle_ID,

	//enemy
	MedusaHeads_ID,
	Bats_ID,
	SpearMan_ID,
	BonePillar_ID,
	Ghost_ID,
	VampireBat_ID,
	Eagle_ID,
	Skeletons_ID,
	Fleaman_ID,

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
	TrapDoor_ID,
	CastleGate_ID,
	BreakableBrick_ID,

	//boss
	Medusa_ID,
	Count_Dracula_ID,

	//other
	Water_ID,
	Fire_ID,
	FireBossDie_ID,
	HP_ID,
	GameUI_ID,

	//Item
	VampireKiller_ID,
	MorningStar_ID,
	ChainWhip_ID,
	SmallHeart_ID,
	LargeHeart_ID,
	WhiteMoneyBag_ID,
	PurpleMoneyBag_ID,
	RedMoneyBag_ID,
	ExtraMonneyBag_ID,
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

	//weapon
	Dagger_ID,
	Throw_Axe_ID,
	HolyWater_ID,
	Cross_ID,
	StopWatch_ID,
};
enum EStairType
{
	UpRight,
	UpLeft,
	DownRight,
	DownLeft,
	None_Kind
};
enum ObjectType {
	None,
	Item,
	Enemy_Type,
	Other
};
enum Action
{
	Idle,
	Run_Right,
	Run_Left,
	Jump,
	Fight,
	Sit,
	Fall,
	IntoCastle
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