#pragma once
#include "SceneManager.h"
#include "GameObject.h"

namespace engine
{
	class Scene
	{
		friend Scene& SceneManager::CreateScene(const std::string& name);
	public:

		explicit Scene(const std::string& name);
		~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

		void Add(const std::shared_ptr<GameObject>& object);
		void Initialize();
		void Update(float deltaTime);
		void Render() const;

	private: 
		std::string mName{};
		std::vector < std::shared_ptr<GameObject>> m_Objects{};

		static unsigned int idCounter; 
	};
}
