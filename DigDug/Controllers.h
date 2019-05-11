#pragma once
#include "BaseComponent.h"
#include "Structs.h"
#include "InputManager.h"
#include <map>

namespace GD
{
	class Command;

	class PlayerController : public GD::BaseComponent
	{

	public:
		PlayerController(GD::ControllerIndex index) : m_Index{ index } {};
		~PlayerController();

		void Initialize() override {};
		void Update(float deltaTime) override;

		void AssignButton( GD::ControllerButton button, GD::ButtonState state, GD::Command* command );
		void AssignAxis( GD::ControllerAxis axis, Command* command );

	private:
		GD::ControllerIndex m_Index;
		std::map<std::pair<GD::ControllerButton, GD::ButtonState>, Command*> m_ButtonCommands;
		std::map<GD::ControllerAxis, std::pair<Command*, float>> m_AxisCommands;
	};

	class FygarController : public GD::BaseComponent
	{
	public:
		FygarController() = default;
		~FygarController() = default;

		void Initialize() override {};
		void Update(float deltaTime) override;
	};

	class PookaController : public GD::BaseComponent
	{
	public:
		PookaController() = default;
		~PookaController() = default;

		void Initialize() override {};
		void Update(float deltaTime) override;
	};
}


