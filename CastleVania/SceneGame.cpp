#include "SceneGame.h"

#define BACKGROUND_FILE "Resources/black.png"
#define CAMERA_MOVE_SPEED 4
SceneGame::SceneGame(void) : Scene(EnumSceneState::Scene_Game)
{
	_levelNow = 1;
	_stageNow = 1;
	_playerDie = false;
	camera = new GCamera();
	bg = NULL;
	_stateCamera = ECameraState::Update_Camera;
	score = 0;
	totalResets = 3;
}

SceneGame::~SceneGame()
{
}

void SceneGame::LoadResources(LPDIRECT3DDEVICE9 d3ddv) {
	srand((unsigned)time(NULL));

	D3DXCreateSprite(d3ddv, &G_SpriteHandler);

	//Black background
	background = CreateSurfaceFromFile(d3ddv, BACKGROUND_FILE);
	HRESULT res = D3DXCreateSprite(d3ddv, &G_SpriteHandler);

	// Delete previous background
	if (bg != NULL)
		delete bg;

	LoadLevel(_levelNow);
	LoadStage(_stageNow);
}

void SceneGame::LoadLevel(int level)
{
	//ResetLevel();
	if (qGameObject != NULL)
		delete qGameObject;
	
	camera->viewport.y = 485;
	bg = new BackgroundController(level);
	//bg->LoadQuadTreeFromFile();
	//player = new Player(345, 1310); //-> Stage 6 
	//player = new Player(287, 1310);

	player = new Simon(3776, 130, 32, 64); // stage 1
								  //stage2
								  //player = new Player(3170, 670);

								  // stage 5: - trapdoor, viewport = 1253
								  //		player = new Player(1146, 860); 

	_stageReset = 1;

	// Position to reset

	revivePosition.x = player->x;
	revivePosition.y = player->y;
	cameraPosition = camera->viewport;
}

void SceneGame::RenderFrame(LPDIRECT3DDEVICE9 d3ddv, int t) {


		if (_stateCamera == ECameraState::Update_Camera)
		{
			camera->UpdateCamera(player->x);
		}

		qGameObject->Update(player, t);
		bg->GetAvailableTiles(camera->viewport.x, camera->viewport.y);
		if (G_Device->BeginScene())
		{
			// Clear back buffer with BLACK
			G_Device->ColorFill(G_BackBuffer, NULL, D3DCOLOR_XRGB(0, 0, 0));
			G_SpriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
			//----- start drawing
			player->Update(t);
			player->Collision(*(qGameObject->inSightObjects), t);
			qGameObject->Collision(t);
			G_SpriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
			bg->Draw(camera);
			qGameObject->Draw(camera);
			player->Draw(camera);
			//---- end drawing
			G_SpriteHandler->End();
			G_Device->EndScene();
		}
		
}



void SceneGame::LoadStage(int stage)
{
	qGameObject = new ObjectsManager("Resource/map/lv-2.1OBJ.txt");
	camera->SetSizeMap(4096, 0);	//openDoor = new OpenDoor(posDoor.x, posDoor.y);
}


void SceneGame::ChangeCamera(EDoorDirection _directDoor)
{

	//if (_directDoor != EDoorDirection::NoneDoor)
	//{
	//	switch (_directDoor)
	//	{
	//	case TeleDown:
	//	{
	//		camera->viewport.y -= (32 * 12); //do cao 1 stage = 32pixcel * 12 dong
	//		player->y -= 32;

	//		if (_stageNow >= 1) {
	//			_stageNow--;
	//			LoadStage(_stageNow);
	//		}
	//	}
	//	break;
	//	case TeleUp:
	//	{
	//		camera->viewport.y += (32 * 12); //do cao 1 stage = 32pixcel * 12 dong
	//		player->y += 64;

	//		_stageNow++;
	//		LoadStage(_stageNow);
	//	}
	//	break;
	//	case DoorLeft:
	//	{
	//		_stateCamera = ECameraState::NoUpdate_Camera;
	//		_beginMoveCamera = true;
	//		_firstMoveCameraDone = false;
	//		_secondMoveCameraDone = false;
	//		_rangeMoveCamera = -264;//-264;
	//		_rangeMoveCamera2 = -264;
	//		_rangeMovePlayer = -120; // -120;
	//		_doorDirect = -1;
	//	}
	//	break;
	//	case DoorRight:
	//	{
	//		_stateCamera = ECameraState::NoUpdate_Camera;
	//		_beginMoveCamera = true;
	//		_firstMoveCameraDone = false;
	//		_secondMoveCameraDone = false;
	//		_rangeMoveCamera = 264;
	//		_rangeMoveCamera2 = 264;
	//		_rangeMovePlayer = 120;
	//		_doorDirect = 1;
	//	}
	//	break;
	//	default:
	//		break;
	//	}
	//}

}

void SceneGame::MoveCamera(int &_moveRange)
{
	//if (_rangeMoveCamera == 0)
	//	_rangeMoveCamera = _moveRange;
	//if (_beginMoveCamera)
	//{
	//	player->Stop();
	//	if (_rangeMoveCamera == 0 && !_firstMoveCameraDone)
	//	{
	//		_firstMoveCameraDone = true;
	//		_beginMoveCamera = false;
	//		return;
	//	}
	//	// qua phải
	//	if (_rangeMoveCamera > 0)
	//	{
	//		_rangeMoveCamera -= CAMERA_MOVE_SPEED;
	//		camera->viewport.x += CAMERA_MOVE_SPEED;
	//	}
	//	// qua trái
	//	else
	//	{
	//		_rangeMoveCamera += CAMERA_MOVE_SPEED;
	//		camera->viewport.x -= CAMERA_MOVE_SPEED;
	//	}
	//}
	//else if (_firstMoveCameraDone)
	//{
	//	player->Stop();
	//	if (_rangeMoveCamera2 == 0 && !_secondMoveCameraDone)
	//	{
	//		_firstMoveCameraDone = false;
	//		_beginMoveCamera = false;
	//		_secondMoveCameraDone = true;
	//		_stageNow++;
	//		
	//		LoadStage(_stageNow);
	//		_stateCamera = ECameraState::Update_Camera;
	//		//---------Luu vi tri stage moi de hoi sinh -----------------
	//		_stageReset = _stageNow;
	//		revivePosition.x = player->x;
	//		revivePosition.y = player->y;
	//		cameraPosition = camera->viewport;
	//		//-----------------------------
	//		return;
	//	}
	//	if (_rangeMoveCamera2 > 0)
	//	{
	//		_rangeMoveCamera2 -= CAMERA_MOVE_SPEED;
	//		camera->viewport.x += CAMERA_MOVE_SPEED;
	//	}
	//	else
	//	{
	//		_rangeMoveCamera2 += CAMERA_MOVE_SPEED;
	//		camera->viewport.x -= CAMERA_MOVE_SPEED;
	//	}
	//}

}

void SceneGame::ProcessInput(int KeyCode) {

	switch (KeyCode)
	{
	case DIK_RIGHT:
		player->RunRight();
	case DIK_D:
		player->RunRight();
		break;
	case DIK_LEFT:
		player->RunLeft();
	case DIK_A:
		player->RunLeft();
		break;
	case DIK_DOWN:
			player->Sit();
		break;
	default:
		player->Stop();
		break;
	}
}


void SceneGame::OnKeyDown(int KeyCode) {
	switch (KeyCode)
	{
	case DIK_SPACE:
		player->Jump();
		break;
	case DIK_J:
		player->Attack();
		break;
	}

}