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
		GD::State* HandleInput() override;

	private:
		GD::Collider* m_Collider;
	};

	class DigDugBehaviour : public GD::Behaviour 
	{
	public:

		DigDugBehaviour() = default;
		~DigDugBehaviour() = default;

		void Initialize() override;
		GD::State* HandleInput() override;
	
	private:
		GD::Collider* m_Collider;
	};
}


