#pragma once
#include "Game.h"
#include "SceneGame.h"
#include "EnumManager.h"

class SceneControl :
	public CGame
{
public:
	SceneControl(int _nCmdShow);
	~SceneControl();
	Scene* sceneNow;
	EnumSceneState currentStateScene;
protected:

	virtual void RenderFrame(LPDIRECT3DDEVICE9 d3ddv, int t);
	virtual void ProcessInput(LPDIRECT3DDEVICE9 d3ddv, int Delta);
	virtual void LoadResources(LPDIRECT3DDEVICE9 d3ddv);

	virtual void OnKeyDown(int KeyCode);
};

