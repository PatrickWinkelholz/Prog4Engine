#include "pch.h"
#include "DigDugAgents.h"
#include "DigDugCommands.h"

DD::EnemyBaseAgent::EnemyBaseAgent()
	: m_DirectionChangeTimeBounds{ 1.5f, 3.f }
	, m_Timer{ 0 }
{
	m_Commands.push_back(new GD::MoveHorizontal());
	m_Commands.push_back(new GD::MoveVertical());
	ChangeDirection();
}

void DD::EnemyBaseAgent::GenerateInput( const GD::GameObject& gameObject, float elapsedSec) 
{
	m_Timer += elapsedSec;
	if (m_Timer > m_DirectionChangeTime) 
	{
		ChangeDirection();
	}
	m_Commands[0]->Execute( gameObject, m_Direction.x);
	m_Commands[1]->Execute( gameObject, m_Direction.y);
}

void DD::EnemyBaseAgent::ChangeDirection() 
{
	//TODO: make this nice with collision
	m_Timer = 0;
	m_DirectionChangeTime = RandomRange(m_DirectionChangeTimeBounds.x, m_DirectionChangeTimeBounds.y);
	m_Direction = {};
	if (rand() % 2 == 0)
		m_Direction.x = static_cast<float>((rand() % 3) - 1);
	else
		m_Direction.y = static_cast<float>((rand() % 3) - 1);
}

float DD::EnemyBaseAgent::RandomRange( float low, float high ) 
{
	return static_cast<float>((rand() % (
		static_cast<int>(high - low * 1000.f)) +
		static_cast<int>(low * 1000.f))) / 1000.f;
}

DD::FygarAgent::FygarAgent() 
	: EnemyBaseAgent()
{
	m_Commands.push_back(new DD::Attack());
}

void DD::FygarAgent::GenerateInput( const GD::GameObject& gameObject, float elapsedSec)
{
	EnemyBaseAgent::GenerateInput(gameObject, elapsedSec);
}