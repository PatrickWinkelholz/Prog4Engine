#pragma once
#include <Structs.h>

namespace GD 
{
	class GameObject;
	class Scene;
}

namespace DD 
{
	class DigDugPrefabs 
	{
	public:
		static GD::GameObject* CreateMenuButton();
		static GD::GameObject* CreateDigDug( GD::Scene& scene, GD::ControllerIndex index );
		static GD::GameObject* CreatePooka( GD::Scene& scene, GD::ControllerIndex index = GD::ControllerIndex::Any );
		static GD::GameObject* CreateFygar( GD::Scene& scene, GD::ControllerIndex index = GD::ControllerIndex::Any );
	};
}
