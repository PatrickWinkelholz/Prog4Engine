#pragma once
#include "SceneManager.h"

namespace engine
{
	class SceneObject;
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

		void Add(const std::shared_ptr<SceneObject>& object);
		void Update(float deltaTime);
		void Render() const;

	private: 
		std::string mName{};
		std::vector < std::shared_ptr<SceneObject>> mObjects{};

		static unsigned int idCounter; 
	};
}
