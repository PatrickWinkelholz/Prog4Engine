#pragma once
#include "Singleton.h"
#include <string>
#include <vector>

namespace GD
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		Scene& CreateScene(const std::string& name);
		Scene& CreateScene(const std::string&& name);

		void Initialize();
		void Update(float deltaTime);
		void SetActiveScene(GD::Scene& scene);
		void FixedUpdate();
		void Render();

	private:
		std::vector<std::shared_ptr<Scene>> m_Scenes;
		GD::Scene* m_ActiveScene;
	};

}
