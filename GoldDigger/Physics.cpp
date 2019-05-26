#include "GoldDiggerPCH.h"
#include "Physics.h"
#include "GameObject.h"
#include "Collider.h"

const GD::Vector2 GD::Physics::m_Gravity{ 0, 2000.f};

void GD::Physics::Initialize() 
{

}

void GD::Physics::Update( float deltaTime ) 
{
	//TODO: use actual acceleration
	if (m_UseGravity)
		m_Acceleration = m_Gravity * deltaTime;

	m_Velocity = m_MoveDirection.Normalized() * m_MaxSpeed;
	m_Velocity += m_Acceleration;

	//std::cout << m_MoveDirection.Normalized().x << " | " << m_MoveDirection.Normalized().y << '\n';

	/*if (m_Velocity.LengthSquared() > pow(m_MaxSpeed, 2)) {}
		m_Velocity = m_Velocity.Normalized() * m_MaxSpeed;*/

	m_GameObject->SetPosition(m_GameObject->GetPosition() + m_Velocity * deltaTime);

	if (m_Collider && m_AreaTag != "") 
	{
		m_Collider->UpdateCollisionBox();
		if (!m_Collider->IsInside(m_AreaTag.c_str())) 
		{
			m_GameObject->SetPosition(m_GameObject->GetPosition() - m_Velocity * deltaTime);
			m_Collider->UpdateCollisionBox();
		}
	}
}
