#include "GoldDiggerPCH.h"
#include "Scene.h"
#include "GameObject.h"

unsigned int engine::Scene::idCounter = 0;

engine::Scene::Scene(const std::string& name) : mName(name) {}
engine::Scene::~Scene() = default;

void engine::Scene::Add(const std::shared_ptr<GameObject>& object)
{
	m_Objects.push_back(object);
}

void engine::Scene::Initialize() 
{
	for (auto gameObject : m_Objects) 
	{
		gameObject->Initialize();
	}
}

void engine::Scene::Update(float deltaTime)
{
	for(auto gameObject : m_Objects)
	{
		gameObject->Update(deltaTime);
	}
}

void engine::Scene::Render() const
{
	for (const auto gameObject : m_Objects)
	{
		gameObject->Render();
	}
}

