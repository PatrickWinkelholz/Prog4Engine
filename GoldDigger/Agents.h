#pragma once
#include "BaseComponent.h"
#include "structs.h"
#include <map>

namespace GD 
{
	class Command;
	class AxisCommand;
	class GameObject;

	class Agent 
	{
	public:
		Agent() = default;
		virtual ~Agent() = default;

		virtual void HandleInput(GameObject& gameObject) = 0;
	};

	class PlayerInputAgent : public GD::Agent
	{

	public:
		PlayerInputAgent(GD::ControllerIndex index) : m_Index{ index } {};
		~PlayerInputAgent();

		void HandleInput(GameObject& gameObject) override;

		void AssignButton(GD::ControllerButton button, GD::ButtonState state, GD::Command* command);
		void AssignAxis(GD::ControllerAxis axis, AxisCommand* command);

	private:
		GD::ControllerIndex m_Index;
		std::map<std::pair<GD::ControllerButton, GD::ButtonState>, Command*> m_ButtonCommands;
		std::map<GD::ControllerAxis, AxisCommand*> m_AxisCommands;
	};
}

