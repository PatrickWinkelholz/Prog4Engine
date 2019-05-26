#include "pch.h"
#include "DigDugBehaviours.h"
#include "DigDugStates.h"
#include "DigDugStructs.h"
#include <iostream>
#include <GameObject.h>
#include <Components.h>
#include <SceneManager.h>
#include <Scene.h>
#include <Structs.h>

void DD::EnemyBehaviour::Initialize()
{
	m_Collider = GetEntity()->m_GameObject->GetComponent<GD::Collider>();
}

GD::State* DD::EnemyBehaviour::HandleInput(float /*elapsedSec*/)
{
	StateID state = static_cast<StateID>(GetEntity()->GetState()->GetID());

	if (m_Collider)
		if (m_Collider->CollidesWith("rock") && state != StateID::Dying)
			return new Dying();

	if (m_Collider && state != StateID::Pumped)
		if (m_Collider->CollidesWith("projectile"))
			return new Pumped();

	if (GetEntity()->GetInput().startFloat && (state == StateID::Walking || state == StateID::Idle))
		return new Floating();

	if (GetEntity()->GetInput().attack && (state == StateID::Walking || state == StateID::Idle))
	{
		return new Charging( 0.5f );
	}

	return nullptr;
}

void DD::DigDugBehaviour::Initialize() 
{
	m_Collider = GetEntity()->m_GameObject->GetComponent<GD::Collider>();
}

GD::State* DD::DigDugBehaviour::HandleInput(float /*elapsedSec*/)
{
	StateID state = static_cast<StateID>(GetEntity()->GetState()->GetID());

	if (m_Collider && state != StateID::Dying) 
	{
		if (m_Collider->CollidesWith("enemy") || m_Collider->CollidesWith("rock"))
			return new Dying();
	}

	if (m_Collider && state == StateID::Walking) 
	{
		if (!m_Collider->IsInside("tunnel"))
			return new Digging();
	}

	if (GetEntity()->GetInput().attack && (state == StateID::Walking || state == StateID::Idle))
	{
		GD::GameObject* go_Projectile = GD::SceneManager::GetInstance().GetActiveScene()->CreateGameObject( static_cast<unsigned int>(Layer::Foreground) );
		GD::Texture* projectileTexture = go_Projectile->CreateTexture();
		go_Projectile->AddComponent(new GD::Sprite(projectileTexture, "Projectile"));
		go_Projectile->AddComponent(new GD::Collider(projectileTexture, "projectile", 2.0f));
		GD::Physics* physics = new GD::Physics(50.f, false);
		physics->SetMoveDirection({ 50.f, 0 });
		go_Projectile->AddComponent(physics);
		go_Projectile->SetPosition(GetEntity()->m_GameObject->GetPosition());
		return new Attacking(0.5f, go_Projectile);
	}

	return nullptr;
}


void DD::RockBehaviour::Initialize()
{
	m_LastPos = GetEntity()->m_GameObject->GetPosition();
	m_Physics = GetEntity()->m_GameObject->GetComponent<GD::Physics>();
	m_Collider = GetEntity()->m_GameObject->GetComponent<GD::Collider>();
}

GD::State* DD::RockBehaviour::HandleInput( float elapsedSec )
{
	//StateID state = static_cast<StateID>(GetEntity()->GetState()->GetID());

	if (m_WiggleTimer < -0.5f) 
	{
		if (m_LastPos != GetEntity()->m_GameObject->GetPosition())
		{
			GetEntity()->m_GameObject->SetPosition(m_LastPos);
			if (m_Physics)
				m_Physics->SetEnabled(false);
			m_WiggleTimer = 1.0f;
		}
	}	
	else if (m_WiggleTimer < -0.3f) 
	{
		if (abs(m_LastPos.y - GetEntity()->m_GameObject->GetPosition().y) < 0.0001f)
			if (m_Collider)
				m_Collider->SetTag("");
		m_LastPos = GetEntity()->m_GameObject->GetPosition();
	}
	else
	{
		if (m_WiggleTimer >= 0)
			m_WiggleTimer -= elapsedSec;
		if (m_WiggleTimer < 0) 
		{
			if (m_Physics)
				m_Physics->SetEnabled(true);
			m_WiggleTimer = -0.4f;
			m_LastPos = GetEntity()->m_GameObject->GetPosition();
			if (m_Collider)
				m_Collider->SetTag("rock");
		}
	}

	return nullptr;
}