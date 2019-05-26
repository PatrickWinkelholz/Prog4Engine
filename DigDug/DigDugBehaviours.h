#pragma once
#include <Entity.h>

namespace GD 
{
	class State;
	class Collider;
};

namespace DD
{
	class EnemyBehaviour : public GD::Behaviour 
	{
	public:
		EnemyBehaviour() = default;
		~EnemyBehaviour() = default;

		void Initialize() override;
		GD::State* HandleInput(float elapsedSec) override;

	private:
		GD::Collider* m_Collider;
	};

	class DigDugBehaviour : public GD::Behaviour 
	{
	public:

		DigDugBehaviour() = default;
		~DigDugBehaviour() = default;

		void Initialize() override;
		GD::State* HandleInput(float elapsedSec) override;
	
	private:
		GD::Collider* m_Collider;
	};

	class RockBehaviour : public GD::Behaviour 
	{
	public:

		RockBehaviour() = default;
		~RockBehaviour() = default;

		void Initialize() override;
		GD::State* HandleInput(float elapsedSec) override;

	private:
		GD::Vector2 m_LastPos;
		float m_WiggleTimer = -1.0f;
		GD::Physics* m_Physics;
		GD::Collider* m_Collider;
	};
}


