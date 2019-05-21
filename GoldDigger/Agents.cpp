#include "GoldDiggerPCH.h"
#include "Agents.h"
#include "InputManager.h"
#include "Commands.h"

GD::Agent::~Agent()
{
	for (Command* command : m_Commands)
		delete command;
}

void GD::Agent::Initialize( Input* input ) 
{
	for (Command* command : m_Commands) 
	{
		command->m_Input = input;
	}
}

void GD::PlayerInputAgent::GenerateInput(const GameObject& gameObject, float /*elapsedSec*/)
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
	m_Commands.push_back(command);
	m_ButtonCommands[std::make_pair(button, state)] = command;
}

void GD::PlayerInputAgent::AssignAxis(GD::ControllerAxis axis, Command* command)
{
	m_Commands.push_back(command);
	m_AxisCommands[axis] = command;
}
