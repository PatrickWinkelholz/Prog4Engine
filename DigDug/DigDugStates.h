#pragma once
#include <Structs.h>
#include <Entity.h>
#include "DigDugStructs.h"

namespace GD 
{
	class Physics;
	class GameObject;
}

namespace DD 
{
	class Walking : public GD::State 
	{
	public:
		Walking() : State( static_cast<unsigned int>( StateID::Walking ) ), m_Physics( nullptr ) {};
		~Walking() = default;

		void Enter() override;
		GD::State* Update(float elapsedSec) override;
		void Exit() override;
	
	private:
		GD::Physics* m_Physics;
	};

	class Idle : public GD::State 
	{
	public:
		Idle() : State(static_cast<unsigned int>( StateID::Idle)) {};
		~Idle() = default;

		void Enter() override;
		GD::State* Update(float elapsedSec) override;
	};

	class Floating : public GD::State 
	{
	public:
		Floating() : State(static_cast<unsigned int>( StateID::Floating)) {};
		~Floating() = default;

		void Enter() override;
		GD::State* Update(float elapsedSec) override;
		void Exit() override;
	private:
		GD::Physics* m_Physics;
	};

	class Pumping : public GD::State 
	{
	public:
		Pumping() : State(static_cast<unsigned int>( StateID::Pumping)) {};
		~Pumping() = default;

		GD::State* Update(float /*elapsedSec*/) override { return nullptr; };
	};

	class Attacking : public GD::State 
	{
	public:
		Attacking( float attackDuration, GD::GameObject* projectile )
			: State(static_cast<unsigned int>( StateID::Attacking)) 
			, m_Duration( attackDuration )
			, m_Timer( 0 )
			, m_Projectile( projectile )
		{};
		~Attacking() = default;

		GD::State* Update(float elapsedSec) override;
		void Exit() override;

	private:
		float m_Timer;
		float m_Duration;
		GD::GameObject* m_Projectile;
	};

	class Charging : public GD::State 
	{
	public:
		Charging(float chargeDuration)
			: State(static_cast<unsigned int>(StateID::Charging))
			, m_Duration( chargeDuration)
			, m_Timer(0)
		{};
		~Charging() = default;

		GD::State* Update(float elapsedSec) override;

	private:
		float m_Timer;
		float m_Duration;
	};

	class Dying : public GD::State 
	{
	public:
		Dying() : State(static_cast<unsigned int>(StateID::Dying)) {};
		~Dying() = default;

		GD::State* Update(float /*elapsedSec*/) override { return nullptr; };
	};
}