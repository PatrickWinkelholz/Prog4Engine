#pragma once
#include <Structs.h>
#include <SDL_ttf.h>

namespace GD 
{
	class GameObject;
	class Scene;
	class Command;
}

namespace DD 
{
	class ScoreDisplay;

	class DigDugPrefabs 
	{
	public:
		static GD::GameObject* CreateMenuButton(GD::Scene& scene, const std::string&& text, const std::string&& font, GD::Command* command,
			const SDL_Color& onColor = { 255, 255, 0 }, const SDL_Color& offColor = { 255, 255, 255 });

		static GD::GameObject* CreateDigDug( GD::Scene& scene, float x, float y, GD::ControllerIndex index,
			const GD::Vector2& lifeDisplayPosition, const GD::Grid& grid = {});

		static GD::GameObject* CreatePooka( GD::Scene& scene, float x, float y, ScoreDisplay* scoreDisplay,
			GD::ControllerIndex index = GD::ControllerIndex::Any, const GD::Grid& grid = {});

		static GD::GameObject* CreateFygar( GD::Scene& scene, float x, float y, ScoreDisplay* scoreDisplay,
			GD::ControllerIndex index = GD::ControllerIndex::Any, const GD::Grid& grid = {});

		static GD::GameObject* CreateRock(GD::Scene& scene, float x, float y, const GD::Grid& grid);

		static GD::GameObject* CreateTunnel( GD::Scene& scene );

		static void GenerateTunnels(GD::Scene& scene, const GD::Vector2& start, const GD::Vector2& direction,
			int length, const GD::Grid& grid = {});
	};
}
