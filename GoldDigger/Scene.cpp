#include "GoldDiggerPCH.h"
#include "Scene.h"
#include "GameObject.h"
#include <algorithm>

GD::Scene::~Scene() 
{
	for (auto& pair : m_Objects) 
		for (GameObject* object : pair.second)
			delete object;
};

GD::GameObject* GD::Scene::CreateGameObject( unsigned int layer )
{
	/*if (layer > m_MaxLayer)
		m_MaxLayer = layer;*/

	GameObject* object = new GameObject();
	m_NewObjects[layer].push_back(object);
	return object;
}

void GD::Scene::Initialize() 
{
	MergeNewObjects();
}

void GD::Scene::Update(float deltaTime)
{
	//add pending objects to m_Objects and initialize them
	if (m_NewObjects.size() != 0)
		MergeNewObjects();
	
	//update game objects
	for(auto& pair : m_Objects)
		for (GameObject* gameObject : pair.second)
			gameObject->Update(deltaTime);

	//find destroyed objects
	for (auto& pair : m_Objects)
		for (GameObject* gameObject : pair.second)
			if (gameObject->IsDestroyed())
				m_DestroyedObjects[pair.first].push_back(gameObject);

	//delete destroyed game objects
	for (auto& pair : m_DestroyedObjects)
	{
		for (GameObject* gameObject : pair.second)
		{
			m_Objects[pair.first].erase(std::remove(m_Objects[pair.first].begin(), m_Objects[pair.first].end(), gameObject));
			delete gameObject;
		}
	}
	m_DestroyedObjects.clear();
}

void GD::Scene::MergeNewObjects() //Needed to add objects at runtime
{
	for (auto& pair : m_NewObjects) 
	{
		for (GameObject* object : pair.second)
			object->Initialize();

		m_Objects[pair.first].insert(m_Objects[pair.first].end(), pair.second.begin(), pair.second.end());
	}
	m_NewObjects.clear();
}

void GD::Scene::Render() const
{
	for (auto& pair : m_Objects)
		for (const GameObject* gameObject : pair.second)
			gameObject->Render();
}

