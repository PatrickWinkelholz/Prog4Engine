#pragma once
#include <BaseComponent.h>
#include <Agents.h>

namespace GD 
{
	class GameObject;
	class Collider;
}

namespace DD 
{
	//Agents are purely for input (AI)
	class EnemyBaseAgent : public GD::Agent
	{
	public:
		EnemyBaseAgent();
		virtual ~EnemyBaseAgent() = default;

		virtual void GenerateInput(const GD::GameObject& gameObject, float elapsedSec) override;
	
	private:
		void ChangeDirection();
		inline float RandomRange( float low, float high);

		float m_FloatTimer;
		float m_Timer;
		GD::Vector2 m_DirectionChangeTimeBounds;
		GD::Collider* m_Collider;
		float m_DirectionChangeTime;
		GD::Vector2 m_Direction;
	};

	class FygarAgent : public EnemyBaseAgent 
	{
	public:
		FygarAgent();
		~FygarAgent() = default;

		void GenerateInput(const GD::GameObject& gameObject, float elapsedSec) override;

	private:
		float m_AttackTimer;
	};
}

