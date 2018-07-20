#include "Scene.h"



Scene::Scene(EnumSceneState _sceneState)
{
	background = NULL;
	camera = NULL;
	sceneState = _sceneState;
}


void Scene::RenderFrame(LPDIRECT3DDEVICE9 d3ddv, int t)
{
}

void Scene::ProcessInput(int keycode)
{
}

EnumSceneState Scene::GetSceneState()
{
	return sceneState;
}

void Scene::LoadResources(LPDIRECT3DDEVICE9 d3ddv)
{
}

void Scene::OnKeyDown(int KeyCode)
{
}

Scene::~Scene(void)
{
}
