#include "GoldDiggerPCH.h"
#include "SceneManager.h"
#include "Scene.h"

void GD::SceneManager::Update(float deltaTime)
{
	m_ActiveScene->Update( deltaTime );
}

void GD::SceneManager::Initialize() 
{
	for (auto scene : m_Scenes) 
	{
		scene->Initialize();
	}
}

void GD::SceneManager::FixedUpdate() 
{
	
}

void GD::SceneManager::Render()
{
	m_ActiveScene->Render();
}

GD::Scene& GD::SceneManager::CreateScene(const std::string& name)
{
	return CreateScene(name.c_str());
}

GD::Scene& GD::SceneManager::CreateScene(const std::string&& name)
{
	const auto scene = std::shared_ptr<Scene>(new Scene(name));
	m_Scenes.push_back(scene);
	return *scene;
}

void GD::SceneManager::SetActiveScene( GD::Scene& scene ) 
{
	m_ActiveScene = &scene;
}