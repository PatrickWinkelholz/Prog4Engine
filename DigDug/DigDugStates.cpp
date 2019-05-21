#include "pch.h"
#include "DigDugStates.h"
#include <GameObject.h>
#include <Components.h>

void DD::Walking::Update(const GD::GameObject& gameObject, const GD::Input & input, float /*elapsedSec*/)
{
	GD::Physics* physics{ gameObject.GetComponent<GD::Physics>() };
	if (physics)
		physics->SetMoveDirection(input.movement);	
}

void DD::Idle::Update(const GD::GameObject& /*gameObject*/, const GD::Input & /*input*/, float /*elapsedSec*/)
{

}

void DD::Floating::Update(const GD::GameObject& /*gameObject*/, const GD::Input & /*input*/, float /*elapsedSec*/)
{

}

void DD::Pumping::Update(const GD::GameObject& /*gameObject*/, const GD::Input & /*input*/, float /*elapsedSec*/)
{

}

void DD::BreathingFire::Update(const GD::GameObject& /*gameObject*/, const GD::Input & /*input*/, float /*elapsedSec*/)
{

}

void DD::Charging::Update(const GD::GameObject& /*gameObject*/, const GD::Input & /*input*/, float /*elapsedSec*/)
{

}
