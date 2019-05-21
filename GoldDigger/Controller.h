#pragma once
#include "BaseComponent.h"

namespace GD 
{
	class Agent;

	//this component is mostly obsolete, since i decided to couple the agents to the Entity component 
	//(because it has a lot of advantages to have the state, behaviour and controller be owned by the same component)
	//i kept it anyway for the rare case that i want something to be able to receive input that is NOT an entity 
	// (like the menu buttons for example). in this case the input struct for the execute parameter is ignored
	class Controller : public GD::BaseComponent
	{
	public:
		Controller(Agent* agent) : m_Agent(agent) {};
		~Controller();

		void Initialize() override {};
		void Update(float elapsedSec) override;

	private:
		Agent* m_Agent;
	};
}
