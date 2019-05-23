#pragma once
#include "SceneManager.h"
#include "GameObject.h"

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
		GameObject* CreateGameObject();

	private: 

		void MergeNewObjects(); //puts all pending gameObjects into m_Objects 
		//(this is needed to avoid ordering issues when adding objects at runtime)

		std::vector<GameObject*> m_Objects{};
		std::vector<GameObject*> m_NewObjects{};
		std::vector<GameObject*> m_DestroyedObjects{};
	};
}
