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
	class DigDugPrefabs 
	{
	public:
		static GD::GameObject* CreateMenuButton(GD::Scene& scene, const std::string&& text, const std::string&& font, GD::Command* command,
			const SDL_Color& onColor = { 255, 255, 0 }, const SDL_Color& offColor = { 255, 255, 255 });
		static GD::GameObject* CreateDigDug( GD::Scene& scene, GD::ControllerIndex index );
		static GD::GameObject* CreatePooka( GD::Scene& scene, GD::ControllerIndex index = GD::ControllerIndex::Any );
		static GD::GameObject* CreateFygar( GD::Scene& scene, GD::ControllerIndex index = GD::ControllerIndex::Any );
	};
}
