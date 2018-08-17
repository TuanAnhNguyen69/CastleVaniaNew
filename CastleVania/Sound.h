#pragma once
#include "GAudio.h"
#include "dsutil.h"
#include <vector>
#include "Global.h"
#include <list>

using namespace std;

enum EBGSound
{
	EMenuSound,
	EIntroSound,
	ESceneGameSound,
	EBossSound,
	EEndGameSound,
};

enum EEffectSound
{
	EHitSound,
	ECollectItemSound,
	EMorningStarSound,
	EHolyWaterSound,
	EHurtedSound,
	EDeathSound,
	ESelectSound,
	EOpenDoorSound,
	ESpiritBallSound,
	ECrossSound,
};


class Sound
{
private:
	GAudio* audio;

	vector<GSound*> listEffectSound;
	vector<GSound*> listBGSound;

	GSound* menu_S;
	GSound* intro_S;
	GSound* sceneGame_S;
	GSound* boss_S;
	GSound* endGame_S;

	GSound* hit_S;
	GSound* collect_S;
	GSound* morningStar_S;
	GSound* holyWater_S;
	GSound* hurted_S;
	GSound* death_S;
	GSound* select_S;
	GSound* openDoor_S;
	GSound* spiritBall_S;
	GSound* cross_S;

	static Sound* instance;
	

public:
	Sound();
	static Sound* GetInstance();
	static bool BGSound_On;
	static bool EffectSound_On;

	void PlayBGSound(EBGSound);
	void PlayEffectSound(EEffectSound);
	
	void StopAllBGSound();
	void RemoveAllBGM();
	void ResumeBGM();

	
	~Sound();
};

