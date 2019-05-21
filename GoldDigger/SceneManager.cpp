#include "GoldDiggerPCH.h"
#include "SceneManager.h"
#include "Scene.h"

GD::SceneManager::~SceneManager()
{
	for (auto pair : m_Scenes) 
	{
		if (pair.second)
			delete pair.second;
	}
}

void GD::SceneManager::Update(float deltaTime)
{
	m_ActiveScene->Update( deltaTime );
}

void GD::SceneManager::FixedUpdate() 
{
	
}

void GD::SceneManager::Render()
{
	m_ActiveScene->Render();
}

void GD::SceneManager::AddScene(Scene* scene, unsigned int id)
{
	if (m_Scenes[id])
	{
		std::cout << "SceneManager: Scene with id: " << id << " already exists!\n";
		return;
	}

	m_Scenes[id] = scene;
}

void GD::SceneManager::SwitchScene(unsigned int id) 
{
	if (!m_Scenes[id]) 
	{
		std::cout << "SceneManager: Scene with id: " << id << " doesn't exist!\n";
		return;
	}

	m_ActiveScene = m_Scenes[id];
}

void GD::SceneManager::LoadScene(unsigned int id) 
{
	if (!m_Scenes[id])
	{
		std::cout << "SceneManager: Scene with id: " << id << " doesn't exist!\n";
		return;
	}

	//TODO: use threading for this
	m_Scenes[id]->Load();
	m_Scenes[id]->Initialize();

	if (!m_ActiveScene)
		m_ActiveScene = m_Scenes[id];
}
