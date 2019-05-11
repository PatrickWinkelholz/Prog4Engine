#include "pch.h"
#include "Controllers.h"
#include "Command.h"

//TODO: move the player controller to the engine
void GD::PlayerController::Update( float /*deltaTime*/ ) 
{
	for (auto pair : m_ButtonCommands) 
	{
		if (InputManager::GetInstance().GetButton(pair.first.first, m_Index, pair.first.second))
			pair.second->Execute( *m_GameObject );
	}
	for (auto pair : m_AxisCommands)
	{
		m_AxisCommands[pair.first].second = InputManager::GetInstance().GetAxis(pair.first, m_Index);
		pair.second.first->Execute( *m_GameObject );
	}
}

void GD::PlayerController::AssignButton( GD::ControllerButton button, GD::ButtonState state, Command* command ) 
{
	m_ButtonCommands[std::make_pair(button, state)] = command;
}

void GD::PlayerController::AssignAxis(GD::ControllerAxis axis, Command* command) 
{
	m_AxisCommands[axis] = std::make_pair(command, 0.f);
	command->SetData( &m_AxisCommands[axis].second );
}

GD::PlayerController::~PlayerController() 
{
	for (auto pair : m_ButtonCommands) 
	{
		delete pair.second;
	}
	for (auto pair : m_AxisCommands) 
	{
		delete pair.second.first;
	}
}

void GD::PookaController::Update( float /*deltaTime*/ )
{

}

void GD::FygarController::Update( float /*deltaTime*/ )
{

}