#include "GoldDiggerPCH.h"
#include "Physics.h"
#include "GameObject.h"

const GD::Vector2 GD::Physics::m_Gravity{ 0, -9.8f};

void GD::Physics::Initialize() 
{

}

void GD::Physics::Update( float deltaTime ) 
{
	if (m_UseGravity)
		m_Acceleration += m_Gravity * deltaTime;

	m_Velocity = m_MoveDirection.Normalized() * m_MaxSpeed;
	m_Velocity += m_Acceleration;

	//std::cout << m_MoveDirection.Normalized().x << " | " << m_MoveDirection.Normalized().y << '\n';

	/*if (m_Velocity.LengthSquared() > pow(m_MaxSpeed, 2)) {}
		m_Velocity = m_Velocity.Normalized() * m_MaxSpeed;*/

	m_GameObject->SetPosition( m_GameObject->GetPosition() + m_Velocity * deltaTime);
}
