#pragma once
#include <Structs.h>
#include <Entity.h>
#include "DigDugStructs.h"

namespace GD 
{
	class Physics;
	class GameObject;
	class Collider;
	class Sprite;
}

namespace DD 
{
	class Walking : public GD::MoveState 
	{
	public:
		Walking( bool autoHalt = true ) 
			: MoveState(static_cast<unsigned int>(StateID::Walking)) 
			, m_AutoHalt{ autoHalt }
		{};
		~Walking() = default;

		GD::State* Update(float elapsedSec) override;
	private:
		bool m_AutoHalt; // if set, the state will automatically switch to idle when there's no movement input
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
		Pumping(GD::Collider* projectileCollider)
			: State(static_cast<unsigned int>(StateID::Pumping))
			, m_ProjectileCollider (projectileCollider)
		{};

		GD::State* Update(float elapsedSec) override;
		void Exit() override;

	private:
		GD::Collider* m_ProjectileCollider;
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
		bool IsFinished() const { return m_Timer >= m_Duration; };

	private:
		float m_Timer;
		float m_Duration;
	};

	class Dying : public GD::State 
	{
	public:
		Dying( bool autoDestroy = true ) 
			: State(static_cast<unsigned int>(StateID::Dying)) 
			, m_AutoDestroy{ autoDestroy }
		{};
		~Dying() = default;

		void Enter() override;
		GD::State* Update(float elapsedSec) override;

	private:
		GD::Sprite* m_Sprite;
		bool m_AutoDestroy;
	};

	class Pumped : public GD::State 
	{
	public:
		Pumped() : State(static_cast<unsigned int>(StateID::Pumped)), m_Inflating{true} {};
		~Pumped() = default;

		void Enter() override;
		GD::State* Update(float elapsedSec) override;
		GD::Collider* m_Collider;
		void Exit() override;
	private:
		bool m_Inflating;
		GD::Sprite* m_Sprite;
		std::string m_OriginalTag;
	};
}