
#ifndef _EnumManager_H_
#define _EnumManager_H_

static enum EnumSceneState
{
	Scene_Menu,
	Scene_Game,
	Scene_End
};

// Only add enum below 36, from 0 to 36 need to be sync with mapeditor
enum EnumID
{

	//enemy
	MedusaHead_ID,
	Bat_ID,
	SpearGuard_ID,
	BonePillar_ID,
	Ghost_ID,
	PhantomBat_ID,
	Eagle_ID,
	Skeleton_ID,
	Pleaman_ID,


	//ground
	MovingPlatform_ID,
	StairLeft_ID,
	StairRight_ID,
	StairTopLeft_ID,
	StairTopRight_ID,
	StairBotLeft_ID,
	StairBotRight_ID,
	Door_ID,
	Tele_ID,
	Trap_ID,
	Brick_ID,
	Breakable_ID,
	Candle_ID,

	//boss
	Medusa_ID,
	Count_Dracula_ID,

	//Item
	MorningStar_ID,
	SmallHeart_ID,
	BigHeart_ID,
	MoneyBag400_ID,
	MoneyBag700_ID,
	PorkChop_ID,
	Crown_ID,
	TreasureChest_ID,
	DoubleShot_ID,
	TripleShot_ID,
	SpiritBall_ID,
	Cross_ID,
	Axe_ID,
	Boomerang_ID,
	Knife_ID,
	HolyWater_ID,
	StopWatch_ID,

	// Simon
	Simon_ID,
	SimonDeath_ID,

	//MorningStar
	MorningStar_Weapon_ID,

	//weapon
	Axe_Weapon_ID,
	Boomerang_Weapon_ID,
	Knife_Weapon_ID,
	HolyWater_Weapon_ID,
	StopWatch_Weapon_ID,

	//Effect
	HitEffect_ID,

	//Bullet
	Snake_ID,
	Fire_ID,

	//UI
	HP_ID,
	GameUI_ID,


	//Gournd
	//StairDownLeft_ID,
	//StairDownRight_ID,
	None_ID,

	//Enemy lv1
	Panther_ID,
	Zombie_ID,
};

enum EStairType
{
	TopLeft,
	BotLeft,
	TopRight,
	BotRight,
	Left,
	Right,
	NoneType,
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
	Attack,
	Sit,
	Fall,
	IntoCastle,
	UpStair,
	DownStair
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