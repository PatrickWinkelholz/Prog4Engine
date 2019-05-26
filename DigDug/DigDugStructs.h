#pragma once
#include <Structs.h>
//place for general structs / enum specific to DigDug

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
		Digging,
		Dying,
		Pumping,
		Floating,
		Charging,
		Attacking,
		Pumped,
	};

	enum class LayerID : unsigned int 
	{
		Background = 0,
		Tunnel,
		Foreground,
		HUD
	};

	enum class EventID : unsigned int 
	{
		EnemyPumped = 0,
		EnemyCrushed,
		PLayerDied
	};
}
