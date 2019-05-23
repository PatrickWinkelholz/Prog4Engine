#include "GoldDiggerPCH.h"
#include "Entity.h"
#include "Agents.h"
#include "GameObject.h"
#include "Components.h"

void GD::State::Enter(const GameObject& gameObject) 
{
	GD::Sprite* sprite = gameObject.GetComponent<Sprite>();
	if (sprite) 
	{
		sprite->PlayAnimation(m_ID);
	}
}

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
	m_Agent->GenerateInput(*m_GameObject, elapsedSec);
	GD::State* state = m_Behaviour->HandleInput( m_Input, m_State->GetID());
	if (state)
	{
		m_State->Exit( *m_GameObject );
		delete m_State;
		m_State = state;
		m_State->Enter( *m_GameObject );
	}
	m_State->Update( *m_GameObject, m_Input, elapsedSec);
}