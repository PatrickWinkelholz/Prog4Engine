#include "pch.h"
#include "DigDugAgents.h"
#include "DigDugCommands.h"
#include <Collider.h>
#include "GameObject.h"

DD::EnemyBaseAgent::EnemyBaseAgent()
	: m_DirectionChangeTimeBounds{ 1.5f, 3.f }
	, m_Timer{ 0 }
	, m_FloatTimer{ 0 }
{
	m_FloatTimer = RandomRange(3.f, 6.f);
	m_Commands.push_back(new GD::MoveHorizontal());
	m_Commands.push_back(new GD::MoveVertical());
	m_Commands.push_back(new DD::Float());
	ChangeDirection();
}

void DD::EnemyBaseAgent::GenerateInput( const GD::GameObject& gameObject, float elapsedSec) 
{
	StateID state = static_cast<StateID>(GetEntity()->GetState()->GetID());
	
	m_Timer += elapsedSec;

	if (state == StateID::Floating) 
	{
		if (m_Timer > 0.2f) 
		{
			m_Timer = 0;
			GD::GameObject* nearestPlayer = GD::Collider::FindNearest(gameObject.GetPosition(), "player");
			if (nearestPlayer) 
			{
				m_Direction = (nearestPlayer->GetPosition() - gameObject.GetPosition()).Normalized();
				m_Direction.y *= -1.f;
			}
		}
	}
	else if (state != StateID::Attacking || state != StateID::Charging)
	{
		if (m_Timer > m_DirectionChangeTime)
		{
			ChangeDirection();
		}

		m_FloatTimer -= elapsedSec;
		if (m_FloatTimer < 0) 
		{
			m_FloatTimer = RandomRange(3.f, 6.f);
			m_Timer = 0.3f;
			m_Commands[2]->Execute(gameObject, 0);
		}
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
	, m_AttackTimer{ 0 }
{
	m_Commands.push_back(new DD::Attack());
}

void DD::FygarAgent::GenerateInput( const GD::GameObject& gameObject, float elapsedSec)
{
	m_AttackTimer += elapsedSec;
	if (m_AttackTimer > 0.2f) 
	{
		m_AttackTimer = 0;
		GD::GameObject* nearestPlayer = GD::Collider::FindNearest(gameObject.GetPosition(), "player");
		if (nearestPlayer)
		{
			if ((nearestPlayer->GetPosition() - gameObject.GetPosition()).LengthSquared() < 5000.f) 
			{
				m_Commands[3]->Execute(gameObject, 0);
				m_AttackTimer = -2.0f;
			}
		}
	}

	EnemyBaseAgent::GenerateInput(gameObject, elapsedSec);
}