#include "pch.h"
#include "DigDugStates.h"
#include <GameObject.h>
#include <Components.h>

void DD::Walking::Enter(const GD::GameObject& gameObject) 
{
	m_Physics = gameObject.GetComponent<GD::Physics>();
	GD::State::Enter( gameObject );
}

void DD::Walking::Update(const GD::GameObject& /*gameObject*/, const GD::Input & input, float /*elapsedSec*/)
{
	if ( m_Physics )
		m_Physics->SetMoveDirection(input.movement);	
}

void DD::Idle::Enter(const GD::GameObject& gameObject) 
{
	GD::Physics* physics = gameObject.GetComponent<GD::Physics>();
	if (physics)
		physics->SetMoveDirection({0, 0});
	GD::State::Enter( gameObject );
}

void DD::Floating::Enter(const GD::GameObject& gameObject) 
{
	m_Physics = gameObject.GetComponent<GD::Physics>();

	GD::GridSnap* gridSnap = gameObject.GetComponent<GD::GridSnap>();
	if (gridSnap)
		gridSnap->SetEnabled(false);
	GD::State::Enter(gameObject);
}

void DD::Floating::Update(const GD::GameObject& /*gameObject*/, const GD::Input& input, float /*elapsedSec*/) 
{
	if (m_Physics)
		m_Physics->SetMoveDirection(input.movement);
}

void DD::Floating::Exit(const GD::GameObject& gameObject)
{
	GD::GridSnap* gridSnap = gameObject.GetComponent<GD::GridSnap>();
	if (gridSnap)
		gridSnap->SetEnabled(true);
	GD::State::Enter(gameObject);
}