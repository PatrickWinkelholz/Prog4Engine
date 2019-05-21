#pragma once
#include "BaseComponent.h"

namespace GD 
{
	class Agent;

	class Controller : public GD::BaseComponent
	{
	public:
		Controller(GD::Agent* agent) : m_Agent(agent) {};
		~Controller();

		void Initialize() override {};
		void Update(float deltaTime) override;

	private:
		GD::Agent* m_Agent;
	};
}
