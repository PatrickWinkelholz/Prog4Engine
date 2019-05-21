#include "GoldDiggerPCH.h"
#include "Scene.h"
#include "GameObject.h"

GD::Scene::~Scene() 
{
	for (auto gameObject : m_Objects) 
	{
		delete gameObject;
	}
};

GD::GameObject* GD::Scene::CreateGameObject()
{
	GameObject* object = new GameObject();
	m_Objects.push_back(object);
	return object;
}

void GD::Scene::Initialize() 
{
	for (auto gameObject : m_Objects) 
	{
		gameObject->Initialize();
	}
}

void GD::Scene::Update(float deltaTime)
{
	for(auto gameObject : m_Objects)
	{
		gameObject->Update(deltaTime);
	}
}

void GD::Scene::Render() const
{
	for (const auto gameObject : m_Objects)
	{
		gameObject->Render();
	}
}

