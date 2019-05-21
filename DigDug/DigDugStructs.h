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
		bool attack;
	};
}
