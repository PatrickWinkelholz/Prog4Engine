#include "GoldDiggerPCH.h"
#include "Scene.h"
#include "GameObject.h"

unsigned int GD::Scene::idCounter = 0;

GD::Scene::Scene(const std::string& name) : mName(name) {}
GD::Scene::~Scene() = default;

void GD::Scene::Add(const std::shared_ptr<GameObject>& object)
{
	m_Objects.push_back(object);
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

