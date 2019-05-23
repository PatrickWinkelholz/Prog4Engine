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

GD::State* DD::EnemyBehaviour::HandleInput() 
{
	StateID state = static_cast<StateID>(GetEntity()->GetState()->GetID());
		
	if (GetEntity()->GetInput().startFloat)
	{
		if (state == StateID::Walking || state == StateID::Idle)
			return new Floating();

		if (state == StateID::Floating)
			return new Idle();
	}

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

	if (GetEntity()->GetInput().attack && (state == StateID::Walking || state == StateID::Idle))
	{
		GD::GameObject* go_Projectile = GD::SceneManager::GetInstance().GetActiveScene()->CreateGameObject();
		GD::Texture* projectileTexture = go_Projectile->CreateTexture();
		go_Projectile->AddComponent(new GD::Sprite(projectileTexture, "Projectile"));
		go_Projectile->AddComponent(new GD::Collider(projectileTexture, "projectile"));
		GD::Physics* physics = new GD::Physics(50.f, false);
		physics->SetMoveDirection({ 50.f, 0 });
		go_Projectile->AddComponent(physics);
		go_Projectile->SetPosition(GetEntity()->m_GameObject->GetPosition());
		return new Attacking(0.5f, go_Projectile);
	}

	return nullptr;
}
