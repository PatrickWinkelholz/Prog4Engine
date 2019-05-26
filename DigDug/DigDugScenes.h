#pragma once
#include <Scene.h>

namespace DD 
{
	class ScoreDisplay;

	class MenuScene : public GD::Scene 
	{
	public:
		MenuScene() = default;
		~MenuScene() = default;

		void Load() override;
	};

	class Level1Scene : public GD::Scene 
	{
	public:
		Level1Scene() = default;
		~Level1Scene() = default;

		void Load() override;
	};

	class Level2Scene : public GD::Scene 
	{
	public:
		Level2Scene() = default;
		~Level2Scene() = default;

		void Load() override;
	};
}

