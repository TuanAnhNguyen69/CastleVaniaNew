#include "Sound.h"

Sound* Sound::instance = NULL;
bool Sound::BGSound_On = true;
bool Sound::EffectSound_On = true;

Sound::Sound()
{
	//BGSound_On = true;
	//EffectSound_On = true;

	audio = new GAudio();
	audio->Init_DirectSound(G_hWnd);

	menu_S = audio->LoadSound("Resource/music/Menu.wav");
	intro_S = audio->LoadSound("Resource/music/Intro.wav");
	sceneGame_S = audio->LoadSound("Resource/music/SceneGame.wav");
	boss_S = audio->LoadSound("Resource/music/Boss.wav");
	endGame_S = audio->LoadSound("Resource/music/Game_Over.wav");

	hit_S = audio->LoadSound("Resource/sound/hit.wav");
	collect_S = audio->LoadSound("Resource/sound/collectitem.wav");
	morningStar_S = audio->LoadSound("Resource/sound/usingwhip.wav");
	holyWater_S = audio->LoadSound("Resource/sound/holywater.wav");
	hurted_S = audio->LoadSound("Resource/sound/hurted.wav");
	death_S = audio->LoadSound("Resource/sound/death.wav");
	select_S = audio->LoadSound("Resource/sound/select.wav");
	openDoor_S = audio->LoadSound("Resource/sound/opendoor.wav");
	spiritBall_S = audio->LoadSound("Resource/sound/spiritball.wav");
	cross_S = audio->LoadSound("Resource/sound/cross.wav");
}



Sound::~Sound()
{
}

Sound * Sound::GetInstance()
{
	if (Sound::instance == NULL)
	{
		instance = new Sound();
	}
	return instance;
}

void Sound::PlayBGSound(EBGSound id)
{
	switch (id)
	{
	case EMenuSound:
		listBGSound.push_back(menu_S);
		if (BGSound_On)
		{
			menu_S->Reset();
			audio->LoopSound(menu_S);
		}
		break;
	case EIntroSound:
		listBGSound.push_back(intro_S);
		if (BGSound_On)
		{
			intro_S->Reset();
			audio->LoopSound(intro_S);
		}
		break;
	case ESceneGameSound:
		listBGSound.push_back(sceneGame_S);
		if (BGSound_On)
		{
			sceneGame_S->Reset();
			audio->LoopSound(sceneGame_S);
		}
		break;
	case EBossSound:
		listBGSound.push_back(boss_S);
		if (BGSound_On)
		{
			boss_S->Reset();
			audio->LoopSound(boss_S);
		}
		break;
	case EEndGameSound:
		listBGSound.push_back(endGame_S);
		if (BGSound_On)
		{
			endGame_S->Reset();
			audio->LoopSound(endGame_S);
		}
		break;
	default:
		break;
	}
}

void Sound::PlayEffectSound(EEffectSound id)
{
	if (!EffectSound_On)
		return;
	switch (id)
	{
	case EHitSound:
		hit_S->Play();
		break;
	case ECollectItemSound:
		collect_S->Play();
		break;
	case EMorningStarSound:
		morningStar_S->Play();
		break;
	case EHolyWaterSound:
		holyWater_S->Play();
		break;
	case EHurtedSound:
		hurted_S->Play();
		break;
	case EDeathSound:
		death_S->Play();
		break;
	case ESelectSound:
		select_S->Play();
		break;
	case EOpenDoorSound:
		openDoor_S->Play();
		break;
	case ESpiritBallSound:
		spiritBall_S->Play();
		break;
	case ECrossSound:
		cross_S->Play();
		break;
	default:
		break;
	}
}

void Sound::StopAllBGSound()
{
	for (int i = 0; i < listBGSound.size(); i++)
	{
		listBGSound[i]->Stop();
	}
}

void Sound::RemoveAllBGM()
{
	StopAllBGSound();
	listBGSound.clear();
}

void Sound::ResumeBGM()
{
	for (int i = 0; i < listBGSound.size(); i++)
	{
		audio->PlaySoundA(listBGSound[i]);
	}
}

