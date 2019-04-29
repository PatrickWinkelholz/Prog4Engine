#include "MiniginPCH.h"
#include "SceneManager.h"
#include "Scene.h"

void engine::SceneManager::Update(float deltaTime)
{
	for(auto scene : mScenes)
	{
		scene->Update(deltaTime);
	}
}

void engine::SceneManager::FixedUpdate() 
{
	
}

void engine::SceneManager::Render()
{
	//only one scene should render
	for (const auto scene : mScenes)
	{
		scene->Render();
	}
}

engine::Scene& engine::SceneManager::CreateScene(const std::string& name)
{
	const auto scene = std::shared_ptr<Scene>(new Scene(name));
	mScenes.push_back(scene);
	return *scene;
}
