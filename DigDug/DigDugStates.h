#pragma once
#include <Structs.h>

namespace DD 
{
	class Walking : public GD::State 
	{
	public:
		Walking() = default;
		~Walking() = default;

		void Enter() override {};
		void Update( const GD::GameObject& gameObject, const GD::Input& input, float elapsedSec);
		void Exit() override {};
	};

	class Idle : public GD::State 
	{
	public:
		Idle() = default;
		~Idle() = default;

		void Enter() override {};
		void Update( const GD::GameObject& gameObject, const GD::Input& input, float elapsedSec);
		void Exit() override {};
	};

	class Floating : public GD::State 
	{
	public:
		Floating() = default;
		~Floating() = default;

		void Enter() override {};
		void Update( const GD::GameObject& gameObject, const GD::Input& input, float elapsedSec);
		void Exit() override {};
	};

	class Pumping : public GD::State 
	{
	public:
		Pumping() = default;
		~Pumping() = default;

		void Enter() override {};
		void Update( const GD::GameObject& gameObject, const GD::Input& input, float elapsedSec);
		void Exit() override {};
	};

	class BreathingFire : public GD::State 
	{
	public:
		BreathingFire() = default;
		~BreathingFire() = default;

		void Enter() override {};
		void Update( const GD::GameObject& gameObject, const GD::Input& input, float elapsedSec);
		void Exit() override {};
	};

	class Charging : public GD::State 
	{
	public:
		Charging() = default;
		~Charging() = default;

		void Enter() override {};
		void Update( const GD::GameObject& gameObject, const GD::Input& input, float elapsedSec);
		void Exit() override {};
	};
}