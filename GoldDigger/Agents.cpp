#include "GoldDiggerPCH.h"
#include "Agents.h"
#include "InputManager.h"
#include "Commands.h"

GD::PlayerInputAgent::~PlayerInputAgent()
{
	for (auto pair : m_ButtonCommands)
		delete pair.second;

	for (auto pair : m_AxisCommands)
		delete pair.second;
}

void GD::PlayerInputAgent::HandleInput(GameObject& gameObject)
{
	for (auto pair : m_ButtonCommands)
	{
		if (InputManager::GetInstance().GetButton(pair.first.first, m_Index, pair.first.second))
			pair.second->Execute(gameObject);
	}
	for (auto pair : m_AxisCommands)
	{
		pair.second->Execute(gameObject, InputManager::GetInstance().GetAxis(pair.first, m_Index));
	}
}

void GD::PlayerInputAgent::AssignButton(GD::ControllerButton button, GD::ButtonState state, Command* command)
{
	m_ButtonCommands[std::make_pair(button, state)] = command;
}

void GD::PlayerInputAgent::AssignAxis(GD::ControllerAxis axis, AxisCommand* command)
{
	m_AxisCommands[axis] = command;
}
