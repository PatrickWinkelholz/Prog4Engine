#include "pch.h"
#include "DigDugStates.h"
#include <GameObject.h>
#include <Components.h>
#include <Entity.h>
#include <SceneManager.h>
#include <Scene.h>
#include "DigDugPrefabs.h"

GD::State* DD::Walking::Update(float elapsedSec)
{
	if (m_AutoHalt) 
	{
		float moveLength{ GetEntity()->GetInput().movement.LengthSquared() };

		if (moveLength == 0)
			return new Idle();
	}

	return MoveState::Update(elapsedSec);
}

void DD::Digging::Enter() 
{
	m_Collider = GetEntity()->m_GameObject->GetComponent<GD::Collider>();
	GD::MoveState::Enter();
}

GD::State* DD::Digging::Update(float elapsedSec) 
{
	GD::Vector2 pos{ GetEntity()->m_GameObject->GetPosition() };
	if (!m_LastTunnel) 
	{
		m_LastTunnel = GD::Collider::FindNearest(pos, "tunnel");
		if (!m_LastTunnel)
		{
			m_LastTunnel = DD::DigDugPrefabs::CreateTunnel(*GD::SceneManager::GetInstance().GetActiveScene());
			m_LastTunnel->SetPosition(GetEntity()->m_GameObject->GetPosition());
		}
	}		
	
	if ((m_LastTunnel->GetPosition() - pos).LengthSquared() >= 4.f * 4.f)
	{
		if (m_Collider)
			if (m_Collider->IsInside("tunnel"))
				return new Walking();

		m_LastTunnel = DD::DigDugPrefabs::CreateTunnel(*GD::SceneManager::GetInstance().GetActiveScene());
		m_LastTunnel->SetPosition(pos);
	}

	float moveLength{ GetEntity()->GetInput().movement.LengthSquared() };
	if (moveLength == 0)
		return new Idle();

	return MoveState::Update(elapsedSec);
}

void DD::Idle::Enter() 
{
	GD::Physics* physics = GetEntity()->m_GameObject->GetComponent<GD::Physics>();
	if (physics)
		physics->SetMoveDirection({0, 0});
	GD::State::Enter();
}

GD::State* DD::Idle::Update( float /*elapsedSec*/ ) 
{
	float moveLength{ GetEntity()->GetInput().movement.LengthSquared() };

	if (moveLength > 0)
		return new Walking();
	return nullptr;
}

void DD::Floating::Enter() 
{
	m_Timer = 0.5f;
	m_Collider = GetEntity()->m_GameObject->GetComponent<GD::Collider>();
	GD::GridSnap* gridSnap = GetEntity()->m_GameObject->GetComponent<GD::GridSnap>();
	if (gridSnap)
		gridSnap->SetEnabled(false);

	GD::MoveState::Enter();

	if (m_Physics)
		m_Physics->SetAreaTag("");
}

GD::State* DD::Floating::Update(float elapsedSec) 
{
	if (m_Timer > 0)
		m_Timer -= elapsedSec;
	else if (m_Collider->IsInside("tunnel"))
		return new Idle();
		
	return MoveState::Update(elapsedSec);
}

void DD::Floating::Exit()
{
	GD::GridSnap* gridSnap = GetEntity()->m_GameObject->GetComponent<GD::GridSnap>();
	if (gridSnap)
		gridSnap->SetEnabled(true);

	if (m_Physics)
		m_Physics->SetAreaTag("tunnel");

	GD::MoveState::Exit();
}

GD::State* DD::Charging::Update(float elapsedSec) 
{
	m_Timer += elapsedSec;
	return nullptr;
}

void DD::Attacking::Enter() 
{
	if (m_Projectile)
		m_ProjectileCollider = m_Projectile->GetComponent<GD::Collider>();
	GD::State::Enter();
}

GD::State* DD::Attacking::Update(float elapsedSec) 
{
	m_Timer += elapsedSec;
	if (m_Timer > m_Duration)
		return new Idle();

	if (m_ProjectileCollider) 
	{
		if (m_ProjectileCollider->GetTag() == "projectile")
		{
			m_ProjectileCollider->UpdateCollisionBox();
			if (m_ProjectileCollider->CollidesWith("enemy")
				|| m_ProjectileCollider->CollidesWith("pumpedEnemy")) 
			{
				Pumping* pumping = new Pumping(m_ProjectileCollider);
				GD::Physics* projectilePhysics = m_Projectile->GetComponent<GD::Physics>();
				if (projectilePhysics)
					projectilePhysics->SetMoveDirection(GD::Vector2{ 0, 0 });
				m_Projectile = nullptr;
				return pumping;
			}
			if (!m_ProjectileCollider->IsInside("tunnel"))
				return new Idle();
		}
	}

	return nullptr;
}

void DD::Attacking::Exit() 
{
	if (m_Projectile)
		m_Projectile->Destroy();
}

GD::State* DD::Pumping::Update(float /*elapsedSec*/) 
{
	float moveLength{ GetEntity()->GetInput().movement.LengthSquared() };

	if (moveLength > 0)
		return new Walking();

	if (m_ProjectileCollider)
		if (!m_ProjectileCollider->CollidesWith("pumpedEnemy"))
			return new Idle();

	return nullptr;
}

void DD::Pumping::Exit() 
{
	if (m_ProjectileCollider)
		m_ProjectileCollider->m_GameObject->Destroy();
}

void DD::Pumped::Enter() 
{
	m_Collider = GetEntity()->m_GameObject->GetComponent<GD::Collider>();
	if (m_Collider) 
	{
		m_OriginalTag = m_Collider->GetTag();
		m_Collider->SetTag("pumpedEnemy");
	}
	m_Sprite = GetEntity()->m_GameObject->GetComponent<GD::Sprite>();
	if (m_Sprite)
		m_Sprite->SetRenderMode(GD::RenderMode::centerLeft);
	GD::State::Enter();
}

GD::State* DD::Pumped::Update(float/* elapsedSec*/) 
{
	if (m_Collider && m_Sprite) 
	{
		if (static_cast<bool>(m_Collider->CollidesWith("projectile")) != m_Inflating) 
		{
			m_Sprite->ReverseAnimation();
			m_Inflating = !m_Inflating;
		}

		if (m_Sprite->GetTimer() < -0.5f) 
		{
			if (m_Inflating) 
			{
				GetEntity()->GetSubject()->Notify(GetEntity(), static_cast<unsigned int>(EventID::EnemyPumped));
				GetEntity()->m_GameObject->Destroy();
			}
			else
				return new Idle();
		}
	}	
	return nullptr;
}

void DD::Pumped::Exit() 
{
	if (m_Sprite)
		m_Sprite->SetRenderMode(GD::RenderMode::corner);
	if (m_Collider)
		m_Collider->SetTag(m_OriginalTag.c_str());
}

void DD::Dying::Enter() 
{
	m_Sprite = GetEntity()->m_GameObject->GetComponent<GD::Sprite>();
	GD::Collider* collider = GetEntity()->m_GameObject->GetComponent<GD::Collider>();
	if (collider)
		collider->SetTag("");

	GD::State::Enter();
}

GD::State* DD::Dying::Update(float /*elapsedSec*/) 
{
	if (m_Sprite && m_AutoDestroy)
		if (m_Sprite->GetTimer() < -0.5f)
			GetEntity()->m_GameObject->Destroy();

	return nullptr;
}