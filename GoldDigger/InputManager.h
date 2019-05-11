#pragma once
#include <map>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <xinput.h>
#include "Singleton.h"
#include "Structs.h"

//----------------------------------------------------------------------------------
// Input manager of GoldDigger engine:
// 
// GoldDigger is designed for local multiplayer games that are controlled using a gamepad
// Keyboard controls are supported but the keyboard is treated like a controller, so in
// the games 'initialize' function InputManager::MapKeyboard should be called to allow
// the keyboard to be used as a controller and setup the button map.
// after that IsPressed, IsDown, IsReleased and GetAxis can be used to get the input from
// the corresponding user
//----------------------------------------------------------------------------------=

namespace GD
{
	enum class ControllerButton
	{
		DPadUp = XINPUT_GAMEPAD_DPAD_UP,
		DPadDown = XINPUT_GAMEPAD_DPAD_DOWN,
		DPadLeft = XINPUT_GAMEPAD_DPAD_LEFT,
		DPadRight = XINPUT_GAMEPAD_DPAD_RIGHT,
		Start = XINPUT_GAMEPAD_START,
		Back = XINPUT_GAMEPAD_BACK,
		LeftStick = XINPUT_GAMEPAD_LEFT_THUMB,
		RightStick = XINPUT_GAMEPAD_RIGHT_THUMB,
		LeftBumper = XINPUT_GAMEPAD_LEFT_SHOULDER,
		RightBumper = XINPUT_GAMEPAD_RIGHT_SHOULDER,
		A = XINPUT_GAMEPAD_A,
		B = XINPUT_GAMEPAD_B,
		X = XINPUT_GAMEPAD_X,
		Y = XINPUT_GAMEPAD_Y
	};

	//tells the inputmanager which SDL_SCANCODE key should be associated with each XBox
	//controller button
	struct KeyboardMap
	{
		WORD DPadUp = 0;
		WORD DPadDown = 0;
		WORD DPadLeft = 0;
		WORD DPadRight = 0;
		WORD Start = 0;
		WORD Back = 0;
		WORD LeftStick = 0;
		WORD RightStick = 0;
		WORD LeftBumper = 0;
		WORD RightBumper = 0;
		WORD A = 0;
		WORD B = 0;
		WORD X = 0;
		WORD Y = 0;
		WORD LeftStickLeft = 0;
		WORD LeftStickRight = 0;
		WORD LeftStickUp = 0;
		WORD LeftStickDown = 0;
		WORD RightStickLeft = 0;
		WORD RightStickRight = 0;
		WORD RightStickUp = 0;
		WORD RightStickDown = 0;
		WORD LeftTrigger = 0;
		WORD RightTrigger = 0;
	};

	class InputManager : public Singleton<InputManager>
	{
	public:
		InputManager();
		~InputManager();

		bool ProcessInput();
		void MapKeyboard( const KeyboardMap& map );

		// returns if <button> of controller with <index> is <pressed/down/released>
		bool GetButton( ControllerButton button, ControllerIndex index, ButtonState state) const;
		
		// ranges from -1.f to 1.f for sticks
		// ranges from 0 to 1.f for triggers
		float GetAxis(ControllerAxis axis, ControllerIndex index) const;

		//TODO: implement this. no hot plug support atm
		//int UpdateConnectedControllers() const;

		//void AssignCommand(ControllerButton button, Command* command);

	private:
		// helper function to translate SDL keyboard input to XINPUT controller input
		void GetKeyboardState( XINPUT_STATE& state, const KeyboardMap& map ) const;

		// maximum nr of supported input devices (four controllers + keyboard)
		static const int m_StatesLength{ 5 };

		// first is current state, second is last state
		std::pair<XINPUT_STATE*, XINPUT_STATE*> m_States[m_StatesLength];
		
		KeyboardMap m_KeyboardMap;
		int m_ConnectedControllers;
		//std::map<ControllerButton, Command*> m_Commands;
	};
}