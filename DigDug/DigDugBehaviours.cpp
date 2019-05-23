#include "pch.h"
#include "DigDugBehaviours.h"
#include "DigDugStates.h"
#include "DigDugStructs.h"
#include <iostream>

GD::State* DD::EnemyBehaviour::HandleInput( GD::Input& input, unsigned int stateID) 
{
	StateID state = static_cast<StateID>(stateID);

	if (input.attack && (state == StateID::Walking || state == StateID::Idle)) 
	{
		input.attack = false;
		return new BreathingFire();
	}

	if (input.startFloat) 
	{
		input.startFloat = false;
		if (state == StateID::Walking || state == StateID::Idle)
			return new Floating();
		if (state == StateID::Floating)
			return new Idle();
	}
		
	float moveLength{ input.movement.LengthSquared() };

	if (moveLength == 0 && state == StateID::Walking)
		return new Idle();

	if (moveLength > 0 && state == StateID::Idle)
		return new Walking();

	return nullptr;
}

GD::State* DD::DigDugBehaviour::HandleInput( GD::Input& input, unsigned int stateID) 
{
	StateID state = static_cast<StateID>(stateID);
/*
	if (input.attack && state == StateID::Walking || state == StateID::Idle)
		return new ();*/

	float moveLength{ input.movement.LengthSquared() };

	if (moveLength == 0 && state == StateID::Walking) {
		return new Idle();
	}

	if (moveLength > 0 && state == StateID::Idle) 
	{
		return new Walking();
	}	

	return nullptr;
}
