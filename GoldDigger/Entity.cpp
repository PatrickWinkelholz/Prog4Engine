#include "GoldDiggerPCH.h"
#include "Entity.h"

void GD::Entity::Update(float /*elapsedSec*/)
{
	GD::State* state = m_Behaviour->HandleInput();
	if (state)
	{
		m_State->Exit();
		delete m_State;
		m_State = state;
		m_State->Enter();
	}
}