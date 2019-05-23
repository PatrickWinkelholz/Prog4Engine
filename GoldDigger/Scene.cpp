#include "GoldDiggerPCH.h"
#include "Scene.h"
#include "GameObject.h"
#include <algorithm>

GD::Scene::~Scene() 
{
	for (GameObject* gameObject : m_Objects) 
	{
		delete gameObject;
	}
};

GD::GameObject* GD::Scene::CreateGameObject()
{
	GameObject* object = new GameObject();
	m_NewObjects.push_back(object);
	return object;
}

void GD::Scene::Initialize() 
{
	MergeNewObjects();
	for (GameObject* gameObject : m_Objects) 
	{
		gameObject->Initialize();
	}
}

void GD::Scene::Update(float deltaTime)
{
	//add pending objects to m_Objects
	if (m_NewObjects.size() != 0) 
	{
		for (GameObject* gameObject : m_NewObjects)
		{
			gameObject->Initialize();
		}
		MergeNewObjects();
	}
	
	//update game objects and find destroyed objects
	for(GameObject* gameObject : m_Objects)
	{
		gameObject->Update(deltaTime);
		if (gameObject->IsDestroyed())
			m_DestroyedObjects.push_back(gameObject);
	}

	//delete destroyed game objects
	if (m_DestroyedObjects.size() != 0) 
	{
		for (GameObject* gameObject : m_DestroyedObjects)
		{
			m_Objects.erase(std::remove(m_Objects.begin(), m_Objects.end(), gameObject));
			delete gameObject;
		}
		m_DestroyedObjects.clear();
	}
}

void GD::Scene::MergeNewObjects() //Needed to add objects at runtime
{
	for (GameObject* gameObject : m_NewObjects) 
	{
		m_Objects.push_back(gameObject);
	}
	m_NewObjects.clear();
}

void GD::Scene::Render() const
{
	for (const GameObject* gameObject : m_Objects)
	{
		gameObject->Render();
	}
}

