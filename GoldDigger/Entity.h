#pragma once
#include "BaseComponent.h"
#include "structs.h"

namespace GD
{
	class Agent;

	class State
	{
	public:
		State(unsigned int id) : m_ID{ id } {};
		virtual ~State() = default;

		virtual void Enter(const GameObject& gameObject);
		virtual void Update(const GameObject& gameObject, const Input& input, float elapsedSec) = 0;
		virtual void Exit(const GameObject& /*gameObject*/) {};

		unsigned int GetID() { return m_ID; };

	protected:
		unsigned int m_ID;
	};

	class EntityBehaviour
	{
	public:
		EntityBehaviour() = default;
		virtual ~EntityBehaviour() = default;

		virtual GD::State* HandleInput( Input& input, unsigned int stateID) = 0;
	};

	class Entity : public BaseComponent
	{
		friend class Command;
	public:
		Entity(EntityBehaviour* behaviour, Agent* agent, State* initialState) 
			: m_Behaviour{ behaviour } 
			, m_Agent{ agent }
			, m_State{ initialState }
		{};
		~Entity();

		void Initialize() override;
		void Update(float elapsedSec) override;

	private:
		EntityBehaviour* m_Behaviour;
		Agent* m_Agent;
		GD::State* m_State;
		Input m_Input;
	};
}

