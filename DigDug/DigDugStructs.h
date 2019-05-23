#pragma once
#include <Structs.h>

namespace DD
{
	enum class GameMode : unsigned int
	{
		SinglePlayer = 0,
		Coop,
		Versus
	};

	enum class Scenes : unsigned int 
	{
		Menu = 0,
		Level1,
		Level2
	};

	struct DigDugInput : GD::Input 
	{
		bool attack = false;
		bool startFloat = false;
	};

	enum class StateID : unsigned int 
	{
		Idle = 0,
		Walking,
		Dying,
		Pumping,
		Floating,
		Charging,
		BreathingFire
	};
}
