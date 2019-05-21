#pragma once
#include <BaseComponent.h>
#include <Agents.h>

class GD::GameObject;

namespace DD 
{
	//Agents are purely for input (AI)
	class FygarAgent : public GD::Agent
	{
	public:
		FygarAgent() = default;
		~FygarAgent() = default;

		void HandleInput(GD::GameObject& gameObject) override;
	};

	class PookaAgent : public GD::Agent
	{
	public:
		PookaAgent() = default;
		~PookaAgent() = default;

		void HandleInput(GD::GameObject& gameObject) override;
	};
}

