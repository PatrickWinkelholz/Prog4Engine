#include "pch.h"
#include "Commands.h"

void MoveHorizontal::Execute(GD::GameObject& gameObject)
{
	//TODO: make this proper
	GD::Vector2 position { gameObject.GetPosition() };
	gameObject.SetPosition( position.x + *m_InputData, position.y);
}

void MoveVertical::Execute(GD::GameObject& gameObject) 
{
	GD::Vector2 position{ gameObject.GetPosition() };
	gameObject.SetPosition(position.x, position.y - *m_InputData);
}