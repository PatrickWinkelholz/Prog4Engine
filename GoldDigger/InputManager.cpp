#include "GoldDiggerPCH.h"
#include "InputManager.h"
#include "Command.h"

GD::InputManager::InputManager() 
	: m_CurrentState{ new XINPUT_STATE() }
	, m_LastState{ new XINPUT_STATE() }
{
	
}

GD::InputManager::~InputManager() 
{
	if (m_CurrentState)
		delete m_CurrentState;
	if (m_LastState)
		delete m_LastState;

	for (auto pair : m_Commands) 
	{
		if (pair.second)
			delete pair.second;
	}
}

void GD::InputManager::AssignCommand(ControllerButton button, Command* command) 
{
	m_Commands[button] = command;
}

bool GD::InputManager::ProcessInput()
{
	(*m_LastState) = *(m_CurrentState);
	XInputGetState(0, m_CurrentState);

	for (auto pair : m_Commands) 
	{
		if (IsPressed(pair.first)) 
			pair.second->execute();
	}

	return true;
}

bool GD::InputManager::IsPressed(ControllerButton button) const
{
	return (m_CurrentState->Gamepad.wButtons & (DWORD)button) 
		&& !(m_LastState->Gamepad.wButtons & (DWORD)button);
}

bool GD::InputManager::IsDown(ControllerButton button) const
{
	return m_CurrentState->Gamepad.wButtons & (DWORD)button;
}

bool GD::InputManager::IsReleased(ControllerButton button) const
{
	return (!m_CurrentState->Gamepad.wButtons & (DWORD)button)
		&& (m_LastState->Gamepad.wButtons & (DWORD)button);
}
