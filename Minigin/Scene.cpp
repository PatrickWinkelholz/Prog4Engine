#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"

unsigned int engine::Scene::idCounter = 0;

engine::Scene::Scene(const std::string& name) : mName(name) {}

engine::Scene::~Scene() = default;

void engine::Scene::Add(const std::shared_ptr<SceneObject>& object)
{
	mObjects.push_back(object);
}

void engine::Scene::Update(float deltaTime)
{
	for(auto gameObject : mObjects)
	{
		gameObject->Update(deltaTime);
	}
}

void engine::Scene::Render() const
{
	for (const auto gameObject : mObjects)
	{
		gameObject->Render();
	}
}

