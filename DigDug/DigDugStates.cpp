#include "pch.h"
#include "DigDugStates.h"
#include <GameObject.h>
#include <Components.h>
#include <Entity.h>
#include <SceneManager.h>
#include <Scene.h>

void DD::Walking::Enter() 
{
	m_Physics = GetEntity()->m_GameObject->GetComponent<GD::Physics>();
	GD::State::Enter();
}

GD::State* DD::Walking::Update(float /*elapsedSec*/)
{
	float moveLength{ GetEntity()->GetInput().movement.LengthSquared() };

	if (moveLength == 0)
		return new Idle();

	if ( m_Physics )
		m_Physics->SetMoveDirection(GetEntity()->GetInput().movement);	

	return nullptr;
}

void DD::Walking::Exit() 
{
	if (m_Physics)
		m_Physics->SetMoveDirection({ 0, 0 });
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
	m_Physics = GetEntity()->m_GameObject->GetComponent<GD::Physics>();

	GD::GridSnap* gridSnap = GetEntity()->m_GameObject->GetComponent<GD::GridSnap>();
	if (gridSnap)
		gridSnap->SetEnabled(false);
	GD::State::Enter();
}

GD::State* DD::Floating::Update( float /*elapsedSec*/) 
{
	if (m_Physics)
		m_Physics->SetMoveDirection(GetEntity()->GetInput().movement);
	return nullptr;
}

void DD::Floating::Exit()
{
	GD::GridSnap* gridSnap = GetEntity()->m_GameObject->GetComponent<GD::GridSnap>();
	if (gridSnap)
		gridSnap->SetEnabled(true);
	if (m_Physics)
		m_Physics->SetMoveDirection({0, 0});
	GD::State::Enter();
}

GD::State* DD::Charging::Update(float elapsedSec) 
{
	m_Timer += elapsedSec;
	if (m_Timer > m_Duration) 
	{
		GD::GameObject* go_Fire = GD::SceneManager::GetInstance().GetActiveScene()->CreateGameObject();
		GD::Texture* FireTexture = go_Fire->CreateTexture();
		go_Fire->AddComponent(new GD::Sprite(FireTexture, "Fire"));
		go_Fire->AddComponent(new GD::Collider(FireTexture, "enemy"));
		GD::Vector2 pos = GetEntity()->m_GameObject->GetPosition();
		go_Fire->SetPosition({ pos.x + 16.f, pos.y });
		return new Attacking(1.0f, go_Fire);
	}
	return nullptr;
}

GD::State* DD::Attacking::Update(float elapsedSec) 
{
	m_Timer += elapsedSec;
	if (m_Timer > m_Duration)
		return new Idle();
	return nullptr;
}

void DD::Attacking::Exit() 
{
	m_Projectile->Destroy();
}