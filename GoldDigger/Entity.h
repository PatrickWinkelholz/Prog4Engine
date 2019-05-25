#pragma once
#include "BaseComponent.h"
#include "structs.h"

namespace GD
{
	class Agent;
	class Behaviour;
	class State;
	class Physics;

	class Entity : public BaseComponent
	{
	public:
		Entity(Behaviour* behaviour, Agent* agent, State* initialState);
		~Entity();

		void Initialize() override;
		void Update(float elapsedSec) override;

		Behaviour* GetBehaviour() const { return m_Behaviour; };
		Agent* GetAgent() const { return m_Agent; };
		State* GetState() const { return m_State; };
		Input GetInput() const { return m_Input; }

	private:
		void ChangeState( State* state);

		Behaviour* m_Behaviour;
		Agent* m_Agent;
		State* m_State;
		Input m_Input;
	};

	class State
	{
		friend class Entity;
	public:
		State(unsigned int id) : m_ID{ id } {};
		virtual ~State() = default;

		virtual void Enter();
		virtual GD::State* Update(float elapsedSec) = 0;
		virtual void Exit() {};

		unsigned int GetID() { return m_ID; };

	protected:
		unsigned int m_ID;
		Entity* GetEntity() const { return m_Entity; };

	private:
		Entity* m_Entity;
	};

	class MoveState : public State
	{
	public: 
		MoveState(unsigned int id) : State(id) {};
		virtual ~MoveState() = default;

		virtual void Enter() override;
		virtual GD::State* Update(float elapsedSec) override;
		virtual void Exit() override;

	protected:
		GD::Physics* m_Physics;
	};

	class Behaviour
	{
		friend Entity::Entity(Behaviour* behaviour, Agent* agent, State* initialState);
	public:
		Behaviour() = default;
		virtual ~Behaviour() = default;

		virtual void Initialize() = 0;
		virtual GD::State* HandleInput() = 0;

	protected:
		Entity* GetEntity() const { return m_Entity; };

	private:
		Entity* m_Entity;
	};
}

