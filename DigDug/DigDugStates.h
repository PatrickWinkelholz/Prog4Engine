#pragma once
#include <Structs.h>
#include <Entity.h>
#include "DigDugStructs.h"

namespace GD 
{
	class Physics;
}

namespace DD 
{
	class Walking : public GD::State 
	{
	public:
		Walking() : State( static_cast<unsigned int>( StateID::Walking ) ), m_Physics( nullptr ) {};
		~Walking() = default;

		void Enter(const GD::GameObject& gameObject) override;
		void Update( const GD::GameObject& gameObject, const GD::Input& input, float elapsedSec) override;
	
	private:
		GD::Physics* m_Physics;
	};

	class Idle : public GD::State 
	{
	public:
		Idle() : State(static_cast<unsigned int>( StateID::Idle)) {};
		~Idle() = default;

		void Enter(const GD::GameObject& gameObject) override;
		void Update(const GD::GameObject& /*gameObject*/, const GD::Input& /*input*/, float /*elapsedSec*/) override {};
	};

	class Floating : public GD::State 
	{
	public:
		Floating() : State(static_cast<unsigned int>( StateID::Floating)) {};
		~Floating() = default;

		void Enter(const GD::GameObject& gameObject) override;
		void Update(const GD::GameObject& /*gameObject*/, const GD::Input& /*input*/, float /*elapsedSec*/) override;
		void Exit(const GD::GameObject& gameObject) override;
	private:
		GD::Physics* m_Physics;
	};

	class Pumping : public GD::State 
	{
	public:
		Pumping() : State(static_cast<unsigned int>( StateID::Pumping)) {};
		~Pumping() = default;

		void Update(const GD::GameObject& /*gameObject*/, const GD::Input& /*input*/, float /*elapsedSec*/) override {};
	};

	class BreathingFire : public GD::State 
	{
	public:
		BreathingFire() : State(static_cast<unsigned int>( StateID::BreathingFire)) {};
		~BreathingFire() = default;

		void Update(const GD::GameObject& /*gameObject*/, const GD::Input& /*input*/, float /*elapsedSec*/) override {};
	};

	class Charging : public GD::State 
	{
	public:
		Charging() : State(static_cast<unsigned int>( StateID::Charging)) {};
		~Charging() = default;

		void Update(const GD::GameObject& /*gameObject*/, const GD::Input& /*input*/, float /*elapsedSec*/) override {};
	};
}