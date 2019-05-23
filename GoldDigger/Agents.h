#pragma once
#include "BaseComponent.h"
#include "structs.h"
#include <map>
#include <vector>
#include "Entity.h"

namespace GD 
{
	class Command;
	class GameObject;

	//Agents are responsible for executing commands.
	//These commands can result in immediate actions (like switching scenes) or they can be
	//used to generate input for an entity (like which buttons were pressed by the player / when does the AI decide to fire / move)
	//This input is then processed by the entity component's Behaviour member
	//The GoldDigger engine user can create his own agents (for AI for example), but the basic player input agent is included in the engine 
	class Agent 
	{
		friend Entity::Entity(Behaviour* behaviour, Agent* agent, State* initialState);
	public:
		Agent() = default;
		virtual ~Agent();

		void Initialize( Input* input );
		virtual void GenerateInput( const GD::GameObject& gameObject, float elapsedSec) = 0;
	
	protected:
		std::vector<Command*> m_Commands;
		Entity* GetEntity() const { return m_Entity; };

	private:
		Entity* m_Entity;
	};

	class PlayerInputAgent : public GD::Agent
	{

	public:
		PlayerInputAgent(GD::ControllerIndex index) : m_Index{ index } {};
		~PlayerInputAgent() = default;

		void GenerateInput( const GD::GameObject& gameObject, float elapsedSec) override;

		void AssignButton(GD::ControllerButton button, GD::ButtonState state, GD::Command* command);
		void AssignAxis(GD::ControllerAxis axis, Command* command);

	private:
		GD::ControllerIndex m_Index;
		std::map<std::pair<GD::ControllerButton, GD::ButtonState>, Command*> m_ButtonCommands;
		std::map<GD::ControllerAxis, Command*> m_AxisCommands;
	};
}

