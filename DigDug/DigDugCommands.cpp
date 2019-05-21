#include "pch.h"
#include "DigDugCommands.h"
#include "DigDug.h"
#include <Entity.h>

void DD::StartGame::Execute(const GD::GameObject& gameObject, float /*axisValue*/) 
{
	DigDug::m_GameMode = m_Mode;
	GD::SwitchScene switchScene{ static_cast<unsigned int>(Scenes::Level1) };
	switchScene.Execute( gameObject );
}

void DD::Attack::Execute(const GD::GameObject& /*gameObject*/, float /*axisValue*/) 
{
	
}