#pragma once
#include <BaseComponent.h>
#include <Agents.h>

class GD::GameObject;

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

		float m_Timer;
		GD::Vector2 m_DirectionChangeTimeBounds;
		float m_DirectionChangeTime;
		GD::Vector2 m_Direction;
	};

	class FygarAgent : public EnemyBaseAgent 
	{
	public:
		FygarAgent();
		~FygarAgent() = default;

		void GenerateInput(const GD::GameObject& gameObject, float elapsedSec) override;
	};
}

