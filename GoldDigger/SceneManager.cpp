#include "GoldDiggerPCH.h"
#include "SceneManager.h"
#include "Scene.h"

void GD::SceneManager::Update(float deltaTime)
{
	//TODO: have only 1 active scene at a time
	for(auto scene : mScenes)
	{
		scene->Update(deltaTime);
	}
}

void GD::SceneManager::Initialize() 
{
	for (auto scene : mScenes) 
	{
		scene->Initialize();
	}
}

void GD::SceneManager::FixedUpdate() 
{
	
}

void GD::SceneManager::Render()
{
	//only one scene should render
	for (const auto scene : mScenes)
	{
		scene->Render();
	}
}

GD::Scene& GD::SceneManager::CreateScene(const std::string& name)
{
	const auto scene = std::shared_ptr<Scene>(new Scene(name));
	mScenes.push_back(scene);
	return *scene;
}