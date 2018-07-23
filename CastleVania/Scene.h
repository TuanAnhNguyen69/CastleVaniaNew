#pragma once

#include <d3dx9.h>
#include <time.h>
#include "Global.h"
#include <string>
#include <iostream>
#include <conio.h>
#include <sstream>
#include "GCamera.h"
#include "EnumManager.h"
#include "Game.h"

class Scene
{
public:
	LPDIRECT3DSURFACE9 background;
	GCamera* camera;
	EnumSceneState sceneState;

	EnumSceneState GetSceneState();
	virtual void RenderFrame(LPDIRECT3DDEVICE9 d3ddv, int t);
	virtual void ProcessInput(int keyCode);
	virtual void LoadResources(LPDIRECT3DDEVICE9 d3ddv);
	virtual void OnKeyDown(int KeyCode);

	LPDIRECT3DSURFACE9 CreateSurfaceFromFile(LPDIRECT3DDEVICE9 d3ddv, char* filePath);

	Scene();
	Scene(EnumSceneState);
	~Scene();
};

