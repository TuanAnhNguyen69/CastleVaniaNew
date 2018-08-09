#ifndef _SCENE1_H_
#define _SCENE1_H_

#include "HeaderObj.h"
#include "Background.h"
#include "Simon.h"
#include "Scene.h"
#include "ObjectsManager.h"

using namespace std;

class SceneGame : public Scene
{
public:

	SceneGame();
	~SceneGame();
protected:
	LPDIRECT3DSURFACE9 BackgroundWhite;
	D3DXVECTOR2 cameraPosition;
	D3DXVECTOR2 revivePosition; //Vi tri hoi sinh
	D3DXVECTOR2 posDoor;
	BackgroundController *bg;
	ObjectsManager* qGameObject;


	int _levelNow, _stageNow;
	GCamera *camera;
	Simon* player;
	
	bool _beginMoveCamera;

	// Score
	int score;
	// Player die
	bool _playerDie;
	int totalResets;
	int resetTime;
	//camera
	void MoveCamera(int &_moveRange);
	void ChangeCamera(EDoorDirection _directDoor);
	ECameraState _stateCamera;
	int _rangeMoveCamera;
	int _rangeMoveCamera2;
	int _rangeMovePlayer;
	

	// door open and close
	int _stageReset;
	
	// UI
	GameUI *gameUI;

	bool _firstMoveCameraDone;	//Di chuyen camera lan 1
	bool _secondMoveCameraDone;	//Di chuyen camera lan 2
	int _doorDirect; //Huong mo cua

	void RenderFrame(LPDIRECT3DDEVICE9 d3ddv, int t);
	void ProcessInput(int keyCode);
	void LoadResources(LPDIRECT3DDEVICE9 d3ddv);
	void LoadLevel(int);
	void LoadStage(int);
	void OnKeyDown(int KeyCode);
};
#endif
