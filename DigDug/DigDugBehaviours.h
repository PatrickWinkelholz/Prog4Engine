#pragma once
#include <Entity.h>

namespace GD 
{
	class State;
	class Collider;
	class Sprite;
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
		GD::Sprite* m_Sprite;
		GD::Vector2 m_StartPos;
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
		GD::Physics* m_Physics;
		GD::Collider* m_Collider;
	};
}


