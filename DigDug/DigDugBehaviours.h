#pragma once
#include <Entity.h>

namespace GD 
{
	class State;
};

namespace DD
{
	class EnemyBehaviour : public GD::EntityBehaviour 
	{
	public:
		EnemyBehaviour() = default;
		~EnemyBehaviour() = default;

		GD::State* HandleInput( GD::Input& Input, unsigned int stateID ) override;
	};

	class DigDugBehaviour : public GD::EntityBehaviour 
	{
	public:

		DigDugBehaviour() = default;
		~DigDugBehaviour() = default;

		GD::State* HandleInput( GD::Input& input, unsigned int stateID) override;
	};
}


