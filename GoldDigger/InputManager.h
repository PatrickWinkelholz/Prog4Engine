#pragma once
#include <map>
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

	private:
		// helper function to translate SDL keyboard input to XINPUT controller input
		void GetKeyboardState( XINPUT_STATE& state, const KeyboardMap& map ) const;

		// maximum nr of supported input devices (four controllers + keyboard)
		static const int m_StatesLength{ 5 };

		// first is current state, second is last state
		std::pair<XINPUT_STATE*, XINPUT_STATE*> m_States[m_StatesLength];
		
		KeyboardMap m_KeyboardMap;
		int m_ConnectedControllers;
	};
}