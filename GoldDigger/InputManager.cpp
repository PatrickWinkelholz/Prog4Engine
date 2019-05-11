#include "GoldDiggerPCH.h"
#include "InputManager.h"
#include "Command.h"
#include <SDL.h>
#include <limits.h>

GD::InputManager::InputManager() 
	: m_States{}
	, m_ConnectedControllers{}
	, m_KeyboardMap{}
{
	for (int i{}; i < m_StatesLength; i++) 
	{
		m_States[i] = std::make_pair<XINPUT_STATE*, XINPUT_STATE*>( new XINPUT_STATE(), new XINPUT_STATE());
	}

	//check how many controllers are connected and get their initial state
	for (int i{}; XInputGetState(i, m_States[i].first) == ERROR_SUCCESS; i++) 
	{
		(*m_States[i+1].second) = *(m_States[i+1].first);
		m_ConnectedControllers++;
		if (m_ConnectedControllers == 4)
			break;
	}
} 

GD::InputManager::~InputManager() 
{
	for (int i{}; i < m_StatesLength; i++) 
	{
		delete m_States[i].first;
		delete m_States[i].second;
	}

	//for (auto pair : m_Commands) 
	//{
	//	if (pair.second)
	//		delete pair.second;
	//}
}

bool GD::InputManager::ProcessInput()
{
	SDL_Event e{  };
	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT)
			return false;
	}

	for (int i{}; i < m_ConnectedControllers+1; i++)
	{
		(*m_States[i].second) = *(m_States[i].first);
		if (i > 0) 
		{
			if (XInputGetState(i-1, m_States[i].first) != ERROR_SUCCESS)
				std::cout << "ERROR: Couldn't read input!\n";
		}
	}

	GetKeyboardState( *m_States[int(ControllerIndex::Keyboard)].first, m_KeyboardMap );

	//Debug input printing
	std::stringstream inputs{};
	for (int index{}; index < m_ConnectedControllers + 1; index++)
	{
		inputs << index << ": LS(" <<
			GetAxis(GD::ControllerAxis::LeftStickX, GD::ControllerIndex(index)) <<
			"|" << GetAxis(GD::ControllerAxis::LeftStickY, GD::ControllerIndex(index)) <<
			") RS: (" << GetAxis(GD::ControllerAxis::RightStickX, GD::ControllerIndex(index)) <<
			"|" << GetAxis(GD::ControllerAxis::RightStickY, GD::ControllerIndex(index)) <<
			") LT: " << GetAxis(GD::ControllerAxis::LeftTrigger, GD::ControllerIndex(index)) <<
			" RT: " << GetAxis(GD::ControllerAxis::RightTrigger, GD::ControllerIndex(index)) << '\n';
	}
	if (inputs.str() != "") std::cout << inputs.str();

	return true;
}

bool GD::InputManager::GetButton(ControllerButton button, ControllerIndex index, ButtonState state) const
{
	if (index != ControllerIndex::Any) 
		for (int i{}; i < m_ConnectedControllers + 1; i++)
			if (GetButton(button, ControllerIndex(i), state))
				return true;

	switch (state)
	{
	case GD::ButtonState::Pressed:
		return (m_States[int(index)].first->Gamepad.wButtons & (DWORD)button)
			&& !(m_States[int(index)].second->Gamepad.wButtons & (DWORD)button);

	case GD::ButtonState::Down:
		return m_States[int(index)].first->Gamepad.wButtons & (DWORD)button;

	case GD::ButtonState::Released:
		return (!m_States[int(index)].first->Gamepad.wButtons & (DWORD)button)
			&& (m_States[int(index)].second->Gamepad.wButtons & (DWORD)button);

	}

	return false;
}

float GD::InputManager::GetAxis(ControllerAxis axis, ControllerIndex index) const 
{
	if (index == ControllerIndex::Any)
		return 0;

	float value{};
	switch (axis)
	{
	case GD::ControllerAxis::LeftStickY:
		value = float(m_States[int(index)].first->Gamepad.sThumbLY);
		return abs(value) > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE ? value / float(SHRT_MAX) : 0;
	case GD::ControllerAxis::LeftStickX:
		value = float(m_States[int(index)].first->Gamepad.sThumbLX);
		return abs(value) > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE ? value / float(SHRT_MAX) : 0;
	case GD::ControllerAxis::RightStickY:
		value = float(m_States[int(index)].first->Gamepad.sThumbRY);
		return abs(value) > XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE ? value / float(SHRT_MAX) : 0;
	case GD::ControllerAxis::RightStickX:
		value = float(m_States[int(index)].first->Gamepad.sThumbRY);
		return abs(value) > XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE ? value / float(SHRT_MAX) : 0;
	case GD::ControllerAxis::LeftTrigger:
		return float(m_States[int(index)].first->Gamepad.bLeftTrigger) / 255.f;
	case GD::ControllerAxis::RightTrigger:
		return float(m_States[int(index)].first->Gamepad.bRightTrigger) / 255.f;
	}
	return 0;
}

//function converts SDL_KeyboardState to XINPUT_STATE 
void GD::InputManager::GetKeyboardState( XINPUT_STATE& state, const GD::KeyboardMap& map ) const
{
	state = std::move(XINPUT_STATE{});
	const Uint8* inState = SDL_GetKeyboardState(nullptr);

	//TODO this can be prettier
	state.Gamepad.wButtons =
		  (inState[map.A]			? WORD(ControllerButton::A)			  : 0)
		| (inState[map.B]			? WORD(ControllerButton::B)			  : 0)
		| (inState[map.X]			? WORD(ControllerButton::X)			  : 0)
		| (inState[map.Y]			? WORD(ControllerButton::Y)			  : 0)
		| (inState[map.Start]		? WORD(ControllerButton::Start)		  : 0)
		| (inState[map.Back]		? WORD(ControllerButton::Back)		  : 0)
		| (inState[map.DPadLeft]	? WORD(ControllerButton::DPadLeft)	  : 0)
		| (inState[map.DPadRight]	? WORD(ControllerButton::DPadRight)   : 0)
		| (inState[map.DPadUp]		? WORD(ControllerButton::DPadUp)	  : 0)
		| (inState[map.DPadDown]	? WORD(ControllerButton::DPadDown)	  : 0)
		| (inState[map.LeftBumper]  ? WORD(ControllerButton::LeftBumper)  : 0)
		| (inState[map.RightBumper] ? WORD(ControllerButton::RightBumper) : 0)
		| (inState[map.LeftStick]	? WORD(ControllerButton::LeftStick)	  : 0)
		| (inState[map.RightStick]	? WORD(ControllerButton::RightStick)  : 0);

	if (inState[map.LeftStickLeft]) state.Gamepad.sThumbLX -= SHRT_MAX;
	if (inState[map.LeftStickRight]) state.Gamepad.sThumbLX += SHRT_MAX;
	if (inState[map.LeftStickUp]) state.Gamepad.sThumbLY += SHRT_MAX;
	if (inState[map.LeftStickDown]) state.Gamepad.sThumbLY -= SHRT_MAX;

	if (inState[map.RightStickLeft]) state.Gamepad.sThumbRX -= SHRT_MAX;
	if (inState[map.RightStickRight]) state.Gamepad.sThumbRX += SHRT_MAX;
	if (inState[map.RightStickUp]) state.Gamepad.sThumbRY += SHRT_MAX;
	if (inState[map.RightStickDown]) state.Gamepad.sThumbRY -= SHRT_MAX;

	state.Gamepad.bLeftTrigger = inState[map.LeftTrigger] * 0xFF;
	state.Gamepad.bRightTrigger = inState[map.RightTrigger] * 0xFF;
}

void GD::InputManager::MapKeyboard( const GD::KeyboardMap& map ) 
{
	m_KeyboardMap = map;
}
