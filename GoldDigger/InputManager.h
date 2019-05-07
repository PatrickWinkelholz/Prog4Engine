#pragma once
#include <map>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <xinput.h>
#include "Singleton.h"

class Command;

namespace GD
{
	enum class ControllerButton
	{
		ButtonA = XINPUT_GAMEPAD_A,
		ButtonB = XINPUT_GAMEPAD_B,
		ButtonX = XINPUT_GAMEPAD_X,
		ButtonY = XINPUT_GAMEPAD_Y,
		ButtonStart = XINPUT_GAMEPAD_START,
		ButtonBack = XINPUT_GAMEPAD_BACK
	};

	class InputManager : public Singleton<InputManager>
	{
	public:
		InputManager();
		~InputManager();

		bool ProcessInput();

		bool IsPressed( ControllerButton button ) const;	//returns true the moment the button is hit
		bool IsDown( ControllerButton button ) const;		//returns true as long as the button is held down
		bool IsReleased( ControllerButton button ) const;	//returns true the moment the button is released

		void AssignCommand(ControllerButton button, Command* command);

	private:
		XINPUT_STATE* m_CurrentState;
		XINPUT_STATE* m_LastState;

		std::map<ControllerButton, Command*> m_Commands;
	};
}