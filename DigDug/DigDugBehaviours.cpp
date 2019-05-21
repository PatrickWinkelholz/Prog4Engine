#include "pch.h"
#include "DigDugBehaviours.h"
#include "DigDugStates.h"

GD::State* DD::EnemyBehaviour::HandleInput( const GD::Input& input) 
{
	if (input.attack)
		return new BreathingFire();

	float moveLength{ input.movement.LengthSquared() };
	float prevMoveLength{ m_PreviousInput.movement.LengthSquared() };

	if (moveLength == 0 && prevMoveLength > 0)
		return new Idle();

	if (moveLength > 0 && prevMoveLength == 0)
		return new Walking();

	m_PreviousInput = input;
	return nullptr;
}

GD::State* DD::DigDugBehaviour::HandleInput( const GD::Input& input ) 
{
	if (input.attack)
		return new BreathingFire();

	float moveLength{ input.movement.LengthSquared() };
	float prevMoveLength{ m_PreviousInput.movement.LengthSquared() };

	if (moveLength == 0 && prevMoveLength > 0)
		return new Idle();

	if (moveLength > 0 && prevMoveLength == 0)
		return new Walking();

	m_PreviousInput = input;
	return nullptr;
}
