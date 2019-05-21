#include "GoldDiggerPCH.h"
#include "Entity.h"
#include "Agents.h"

GD::Entity::~Entity() 
{
	delete m_Agent;
	delete m_Behaviour;
	delete m_State;
}

void GD::Entity::Initialize() 
{
	m_Agent->Initialize( &m_Input );
}

void GD::Entity::Update(float elapsedSec)
{
	//isn't this beautiful?
	m_Agent->GenerateInput(*m_GameObject, elapsedSec);
	GD::State* state = m_Behaviour->HandleInput( m_Input);
	if (state)
	{
		m_State->Exit();
		delete m_State;
		m_State = state;
		m_State->Enter();
	}
	m_State->Update( *m_GameObject, m_Input, elapsedSec);
}