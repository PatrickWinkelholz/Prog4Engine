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

GD::State* DD::EnemyBehaviour::HandleInput() 
{
	StateID state = static_cast<StateID>(GetEntity()->GetState()->GetID());

	if (m_Collider)
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

GD::State* DD::DigDugBehaviour::HandleInput() 
{
	StateID state = static_cast<StateID>(GetEntity()->GetState()->GetID());

	if (m_Collider && state != StateID::Dying) 
	{
		if (m_Collider->CollidesWith("enemy"))
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
