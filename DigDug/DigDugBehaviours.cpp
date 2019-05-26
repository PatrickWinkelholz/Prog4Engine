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

	if (state == StateID::Dying || state == StateID::Pumped)
		return nullptr;		

	if (m_Collider) 
	{
		if (m_Collider->CollidesWith("projectile"))
			return new Pumped();
		else if (m_Collider->CollidesWith("rock")) 
		{
			GetEntity()->GetSubject()->Notify(GetEntity(), static_cast<unsigned int>(EventID::EnemyCrushed));
			return new Dying();
		}
	}	

	if (state == StateID::Charging) 
	{
		if (dynamic_cast<Charging*>(GetEntity()->GetState())->IsFinished()) 
		{
			GD::GameObject* go_Fire = GD::SceneManager::GetInstance().GetActiveScene()->CreateGameObject(static_cast<unsigned int>(LayerID::Foreground));
			GD::Texture* FireTexture = go_Fire->CreateTexture();
			go_Fire->AddComponent(new GD::Sprite(FireTexture, "Fire"));
			go_Fire->AddComponent(new GD::Collider(FireTexture, "enemy"));
			GD::Vector2 pos = GetEntity()->m_GameObject->GetPosition();
			go_Fire->SetPosition({ pos.x + 16.f, pos.y });
			return new Attacking(0.75f, go_Fire);
		}
	}

	if (GetEntity()->GetInput().startFloat && (state == StateID::Walking || state == StateID::Idle))
		return new Floating();

	if (GetEntity()->GetInput().attack && (state == StateID::Walking || state == StateID::Idle))
		return new Charging( 0.5f );

	return nullptr;
}

void DD::DigDugBehaviour::Initialize() 
{
	m_Collider = GetEntity()->m_GameObject->GetComponent<GD::Collider>();
	m_Sprite = GetEntity()->m_GameObject->GetComponent<GD::Sprite>();
	m_StartPos = GetEntity()->m_GameObject->GetPosition();
}

GD::State* DD::DigDugBehaviour::HandleInput(float /*elapsedSec*/)
{
	StateID state = static_cast<StateID>(GetEntity()->GetState()->GetID());

	if (m_Sprite && state == StateID::Dying) 
	{
		if (m_Sprite->GetTimer() < -0.5f) 
		{
			GetEntity()->GetSubject()->Notify(GetEntity(), static_cast<unsigned int>(EventID::PLayerDied));
			GetEntity()->m_GameObject->SetPosition( m_StartPos );
			if (m_Collider)
				m_Collider->SetTag("player");
			return new Idle();
		}
	}

	if (m_Collider && state != StateID::Dying) 
	{
		if (m_Collider->CollidesWith("enemy") || m_Collider->CollidesWith("rock")) 
			return new Dying( false );
	}

	if (m_Collider && state == StateID::Walking) 
	{
		if (!m_Collider->IsInside("tunnel"))
			return new Digging();
	}

	if (GetEntity()->GetInput().attack && (state == StateID::Walking || state == StateID::Idle))
	{
		GD::GameObject* go_Projectile = GD::SceneManager::GetInstance().GetActiveScene()->CreateGameObject( static_cast<unsigned int>(LayerID::Foreground) );
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

GD::State* DD::RockBehaviour::HandleInput( float /*elapsedSec*/ )
{
	StateID state = static_cast<StateID>(GetEntity()->GetState()->GetID());

	if (state == StateID::Idle && abs(m_LastPos.y - GetEntity()->m_GameObject->GetPosition().y) > 0.0001f) 
	{
		GetEntity()->m_GameObject->SetPosition(m_LastPos);
		if (m_Physics)
			m_Physics->SetEnabled( false );
		return new Charging(1.0f);
	}
		
	//charging = rock is about to fall
	if (state == StateID::Charging) 
	{
		if (dynamic_cast<Charging*>(GetEntity()->GetState())->IsFinished()) 
		{
			if (m_Collider)
				m_Collider->SetTag("rock");
			if (m_Physics) 
				m_Physics->SetEnabled(true);
			return new Walking( false );
		}
	}

	//walking = rock is falling
	if (state == StateID::Walking)
		if (m_LastPos == GetEntity()->m_GameObject->GetPosition())
			return new Dying();

	m_LastPos = GetEntity()->m_GameObject->GetPosition();
	return nullptr;
}