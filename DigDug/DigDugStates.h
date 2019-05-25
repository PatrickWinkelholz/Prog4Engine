#pragma once
#include <Structs.h>
#include <Entity.h>
#include "DigDugStructs.h"

namespace GD 
{
	class Physics;
	class GameObject;
	class Collider;
}

namespace DD 
{
	class Walking : public GD::MoveState 
	{
	public:
		Walking() : MoveState( static_cast<unsigned int>( StateID::Walking ) ) {};
		~Walking() = default;

		GD::State* Update(float elapsedSec) override;
	};

	class Idle : public GD::State 
	{
	public:
		Idle() : State(static_cast<unsigned int>( StateID::Idle)) {};
		~Idle() = default;

		void Enter() override;
		GD::State* Update(float elapsedSec) override;
	};

	class Digging : public GD::MoveState 
	{
	public:
		Digging() : MoveState(static_cast<unsigned int>( StateID::Digging)) {};
		~Digging() = default;

		void Enter() override;
		GD::State* Update(float elapsedSec) override;
	
	private:
		GD::GameObject* m_LastTunnel;
		GD::Collider* m_Collider;
	};

	class Floating : public GD::MoveState 
	{
	public:
		Floating() : MoveState(static_cast<unsigned int>( StateID::Floating)) {};
		~Floating() = default;

		void Enter() override;
		GD::State* Update(float elapsedSec) override;
		void Exit() override;
	
	private:
		float m_Timer;
		GD::Collider* m_Collider;
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

		void Enter() override;
		GD::State* Update(float elapsedSec) override;
		void Exit() override;

	private:
		float m_Timer;
		float m_Duration;
		GD::GameObject* m_Projectile;
		GD::Collider* m_ProjectileCollider;
	};

	class Pumping : public GD::State 
	{
	public:
		Pumping(GD::GameObject* projectile)
			: State(static_cast<unsigned int>(StateID::Pumping))
			, m_Projectile(projectile)
		{};

		GD::State* Update(float elapsedSec) override;
		void Exit() override;

	private:
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

	class Pumped : public GD::State 
	{
	public:
		Pumped() : State(static_cast<unsigned int>(StateID::Pumped)) {};
		~Pumped() = default;

		void Enter() override;
		GD::State* Update(float /*elapsedSec*/) override { return nullptr; };
		void Exit() override;
	};
}