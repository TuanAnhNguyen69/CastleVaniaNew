#include "SceneGame.h"

#define BACKGROUND_FILE "Resources/black.png"
#define CAMERA_MOVE_SPEED 4
SceneGame::SceneGame(void) : Scene(EnumSceneState::Scene_Game)
{
	levelNow = 1;
	stageNow = 1;
	playerDie = false;
	camera = new GCamera();
	bg = NULL;
	stateCamera = ECameraState::Update_Camera;
	score = 0;
	totalResets = 3;
	gameUI = NULL;
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

	LoadLevel(levelNow);
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

	player = new Simon(3740, 150);
	//player = new Simon(3776, 130, 32, 64); // stage 1
								  //stage2
								  //player = new Player(3170, 670);

								  // stage 5: - trapdoor, viewport = 1253
								  //		player = new Player(1146, 860); 

	stageReset = 1;

	// Position to reset

	revivePosition.x = player->x;
	revivePosition.y = player->y;
	cameraPosition = camera->viewport;
	gameUI = new GameUI(G_Device, 22, G_ScreenWidth, G_ScreenHeight);
	gameUI->initTimer(100);
	qGameObject = new ObjectsManager("Resource/map/lv-2.1OBJ.txt");
	camera->SetSizeMap(4096, 3572);	//openDoor = new OpenDoor(posDoor.x, posDoor.y);
}

void SceneGame::RenderFrame(LPDIRECT3DDEVICE9 d3ddv, int t) {


	if (stateCamera == ECameraState::Update_Camera)
	{
		camera->UpdateCamera(player->x);
		ChangeCamera(player->GetDirectDoor());
	}
	else {
		door = player->door;
		if (beginMoveCamera)
		{
			MoveCamera(rangeMoveCamera);
		}
		if (firstMoveCameraDone)
		{
			if (!door->isOpen)
				door->RenderOpen();
			if (door->isOpen)
			{	
				if (player->AutoMove(rangeMovePlayer, t))
				{	
					player->doorDirection = EDoorDirection::NoneDoor;
					door->RenderClose();
					player->canPress = false;// lúc đang đóng cửa player không hoạt động
				}
			}
		}

		if (firstMoveCameraDone && !secondMoveCameraDone)
		{
			MoveCamera(rangeMoveCamera2);
		}
		
		if (secondMoveCameraDone)
		{
			player->canPress = true;
			stateCamera = ECameraState::Update_Camera;
		}
	}
		
#pragma endregion 

		if (gameUI->getTimer() <= 0)
		{
			if (levelNow == 1)
				gameUI->initTimer(200);
			else gameUI->initTimer(300);
		}

		player->Update(t);
		gameUI->updateScore(stageNow, player->score, t, player->hp, player->live, player->weaponCount, player->weaponID, 20, player->GetBox().x, player->GetBox().y, player->vX * t, player->vY * t, camera->viewport.x, camera->viewport.y, t);
		qGameObject->Update(player, t);
		player->Collision(*(qGameObject->inSightObjects), t);
		qGameObject->Collision(t);

		bg->GetAvailableTiles(camera->viewport.x, camera->viewport.y);
		//if (G_Device->BeginScene())
		{
			// Clear back buffer with BLACK
			G_Device->ColorFill(G_BackBuffer, NULL, D3DCOLOR_XRGB(0, 0, 0));
			G_SpriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
			//----- start drawing
			bg->Draw(camera);
			qGameObject->Draw(camera);
			//---- end drawing
			gameUI->drawTable();
			player->Draw(camera);
			G_SpriteHandler->End();
			gameUI->drawScore();
		}
}

void SceneGame::SetSizeMap() {
	switch (levelNow) {
	case 1:
		switch (stageNow)
		{
		case 1:
			G_LeftCamera = 3572;
			G_RightCamera = 4096;
			break;
		case 2:
			G_LeftCamera = 3072;
			G_RightCamera = 4096;
			break;
		case 3:
			G_LeftCamera = 1535;
			G_RightCamera = 3072;
			break;
		case 4:
			G_LeftCamera = 1535;
			G_RightCamera = 3072;
			break;
		case 5:
			G_LeftCamera = 0;
			G_RightCamera = 1535;
			break;
		case 6:
			G_LeftCamera = 0;
			G_RightCamera = 1535;
			break;
		default:
			break;
		}
	}
}

void SceneGame::ChangeCamera(EDoorDirection directDoor)
{

	if (directDoor != EDoorDirection::NoneDoor)
	{
		switch (directDoor)
		{
		case TeleDown:
		{
			camera->viewport.y -= (32 * 12); //do cao 1 stage = 32pixcel * 12 dong
			player->y -= 32;

			if (stageNow >= 1) {
				stageNow--;
				player->doorDirection = NoneDoor;
			}
		}
		break;
		case TeleUp:
		{
			camera->viewport.y += (32 * 12); //do cao 1 stage = 32pixcel * 12 dong
			player->y += 64;
			stageNow++;
			player->doorDirection = NoneDoor;

		}
		break;
		case DoorLeft:
		{
			stateCamera = ECameraState::NoUpdate_Camera;
			beginMoveCamera = true;
			firstMoveCameraDone = false;
			secondMoveCameraDone = false;
			rangeMoveCamera = -264;//-264;
			rangeMoveCamera2 = -264;
			rangeMovePlayer = -120; // -120;
			doorDirect = -1;
			stageNow++;
		}
		break;
		case DoorRight:
		{
			stateCamera = ECameraState::NoUpdate_Camera;
			beginMoveCamera = true;
			firstMoveCameraDone = false;
			secondMoveCameraDone = false;
			rangeMoveCamera = 264;
			rangeMoveCamera2 = 264;
			rangeMovePlayer = 120;
			doorDirect = 1;
			stageNow++;

		}
		break;
		default:
			break;
		}
		SetSizeMap();
		camera->SetSizeMap(G_RightCamera, G_LeftCamera);
	}
	

}

void SceneGame::MoveCamera(int &_moveRange)
{
	if (rangeMoveCamera == 0)
		rangeMoveCamera = _moveRange;
	if (beginMoveCamera)
	{
		player->Stop();
		if (rangeMoveCamera == 0 && !firstMoveCameraDone)
		{
			firstMoveCameraDone = true;
			beginMoveCamera = false;
			return;
		}
		// qua phải
		if (rangeMoveCamera > 0)
		{
			rangeMoveCamera -= CAMERA_MOVE_SPEED;
			camera->viewport.x += CAMERA_MOVE_SPEED;
		}
		// qua trái
		else
		{
			rangeMoveCamera += CAMERA_MOVE_SPEED;
			camera->viewport.x -= CAMERA_MOVE_SPEED;
		}
	}
	else if (firstMoveCameraDone)
	{
		player->Stop();
		if (rangeMoveCamera2 == 0 && !secondMoveCameraDone)
		{
			firstMoveCameraDone = false;
			beginMoveCamera = false;
			secondMoveCameraDone = true;
			stageNow++;

			player->doorDirection = EDoorDirection::NoneDoor;
			//---------Luu vi tri stage moi de hoi sinh -----------------
			stageReset = stageNow;
			revivePosition.x = player->x;
			revivePosition.y = player->y;
			cameraPosition = camera->viewport;
			//-----------------------------
			return;
		}
		if (rangeMoveCamera2 > 0)
		{
			rangeMoveCamera2 -= CAMERA_MOVE_SPEED;
			camera->viewport.x += CAMERA_MOVE_SPEED;
		}
		else
		{
			rangeMoveCamera2 += CAMERA_MOVE_SPEED;
			camera->viewport.x -= CAMERA_MOVE_SPEED;
		}
	}


}

void SceneGame::ProcessInput(int KeyCode) {

	switch (KeyCode)
	{
	case DIK_RIGHT:
	case DIK_D:
		player->RunRight();
		break;
	case DIK_LEFT:
	case DIK_A:
		player->RunLeft();
		break;
	case DIK_DOWN:
	case DIK_S:
		player->Sit();
		break;
	case DIK_UP:
	case DIK_W:
		player->goUpStair();
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
	case DIK_K:
		player->KnockBack();
		break;
	case DIK_Q:
		player->UpGradeMorningStar();
	case DIK_1:
		player->UseBoomerang();
		break;
	
	case DIK_2:
		player->UseKnife();
		break;
	case DIK_3:
		player->UseAxe();
		break;
	case DIK_4:
		player->UseHolyWater();
		break;
	}

}