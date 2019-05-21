#pragma once
#include "BaseComponent.h"
#include "structs.h"

namespace GD
{
	class Agent;

	class EntityBehaviour
	{
	public:
		EntityBehaviour() = default;
		virtual ~EntityBehaviour() = default;

		virtual GD::State* HandleInput( const Input& input ) = 0;
	
	protected:
		Input m_PreviousInput;
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

