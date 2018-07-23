#include "State_1.h"



State1::State1() : Scene(EnumSceneState::State_1)
{
	camera = new GCamera();
	background = NULL;
	//bat->sprite = new GSprite(TextureManager::getInstance()->getTexture(EnumID::Bat_ID), 0, 3, 100);
}




State1::~State1()
{

}

void State1::LoadResources(LPDIRECT3DDEVICE9 d3ddv)
{
	srand((unsigned)time(NULL));

	D3DXCreateSprite(d3ddv, &G_SpriteHandler);

	background = CreateSurfaceFromFile(d3ddv, "Resources/sprites/black2.png");
	HRESULT res = D3DXCreateSprite(d3ddv, &G_SpriteHandler);

	/*
	if (background != NULL)
		delete background;
	*/
	
	//simon = new Simon(100, 100);

	//bat = new Bat(100, 100);

	posCamera = camera->viewport;
}

void State1::RenderFrame(LPDIRECT3DDEVICE9 d3ddv, int t)
{
	
	camera->UpdateCamera(100);

	//bat->Update(t);

	//simon->Update(t);

	G_SpriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

	//bat->Draw(camera);
	G_SpriteHandler->End();


	//simon->Draw(camera);

	
}

//void State1::ProcessInput(int KeyCode) {
	/*
	switch (KeyCode)
	{
	case DIK_RIGHT:
		simon->RunRight();
	case DIK_D:
		simon->RunRight();
		break;
	case DIK_LEFT:
		simon->RunLeft();
	case DIK_A:
		simon->RunLeft();
		break;
	default:
		simon->Stop();
		break;
	}
	*/
//}

void State1::OnKeyDown(int KeyCode) {
	/*
	switch (KeyCode)
	{
	case DIK_SPACE:
		simon->Jump();
		break;
	}
	*/
}