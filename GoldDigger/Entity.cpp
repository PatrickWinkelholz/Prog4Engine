#include "GoldDiggerPCH.h"
#include "Entity.h"
#include "Agents.h"
#include "GameObject.h"
#include "Components.h"

void GD::State::Enter() 
{
	GD::Sprite* sprite = GetEntity()->m_GameObject->GetComponent<Sprite>();
	if (sprite) 
	{
		sprite->PlayAnimation(m_ID);
	}
}

GD::Entity::Entity(Behaviour* behaviour, Agent* agent, State* initialState)
	: m_Behaviour{ behaviour }
	, m_Agent{ agent }
	, m_State{ initialState }
{
	m_Behaviour->m_Entity = this;
	m_Agent->m_Entity = this;
	m_State->m_Entity = this;
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
	m_Behaviour->Initialize();
}

void GD::Entity::Update(float elapsedSec)
{
	//ok this might look weird but hear me out.
	//The entity component makes it really easy for Agents (resposible for input), Behaviours (responsible for object specific behaviour) and
	//States (responsible for state specific behaviour) to communicate, as usually you have exactly one of each of them on a gameObject
	//differentiating between behaviours and states allows maximum reuseability, since all diffferent gameObjects can use the pretty generic 'walking'
	//state for example, which only does walking specific actions. the alternative would be to only have states, which would make this
	//function look a bit nicer but then i would need a 'FygarWalking', 'DigDugWalking' state and so on.

	m_Input = {};
	m_Agent->GenerateInput(*m_GameObject, elapsedSec);
	GD::State* state = m_Behaviour->HandleInput();
	if (state)
		ChangeState(state);
	state = m_State->Update( elapsedSec);
	if (state)
		ChangeState(state);
}

void GD::Entity::ChangeState( GD::State* state ) 
{
	m_State->Exit();
	delete m_State;
	m_State = state;
	m_State->m_Entity = this;
	m_State->Enter();
}
