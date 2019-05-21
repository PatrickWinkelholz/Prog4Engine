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

	protected:
		GameObject* CreateGameObject();

	private: 
		std::vector<GameObject*> m_Objects{};
	};
}
