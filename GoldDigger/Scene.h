#pragma once
#include "SceneManager.h"
#include "GameObject.h"
#include <map>

namespace GD
{
	class Scene
	{
	public:

		Scene() = default;
		virtual ~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

		void Initialize();
		void Update(float deltaTime);
		void Render() const;
		
		virtual void Load() = 0;
		GameObject* CreateGameObject( unsigned int layer = 0);

	private: 

		void MergeNewObjects(); //puts all pending gameObjects into m_Objects 
		//(this is needed to avoid ordering issues when adding objects at runtime)

		std::map<unsigned int, std::vector<GameObject*>> m_Objects;
		std::map<unsigned int, std::vector<GameObject*>> m_NewObjects;
		std::map<unsigned int, std::vector<GameObject*>> m_DestroyedObjects;
		//unsigned int m_MaxLayer;
	};
}
