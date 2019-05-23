#pragma once
#include "Singleton.h"
#include <string>
#include <map>

namespace GD
{
	class Scene;

	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		~SceneManager();

		void AddScene( Scene* scene, unsigned int id);
		void SwitchScene(unsigned int id);
		void LoadScene(unsigned int id);

		void Update(float deltaTime);
		void FixedUpdate();
		void Render();

		GD::Scene* GetActiveScene() const { return m_ActiveScene; };

	private:
		std::map<unsigned int, Scene*> m_Scenes;
		GD::Scene* m_ActiveScene;
	};

}
