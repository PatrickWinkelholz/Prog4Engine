#pragma once
#include <Commands.h>
#include <GameObject.h>
#include "DigDugStructs.h"

namespace DD
{
	class StartGame : public GD::Command
	{
	public:
		StartGame(GameMode mode) : m_Mode{ mode } {};
		~StartGame() = default;

		void Execute(GD::GameObject& gameObject) override;

	private:
		GameMode m_Mode;
	};

	class Attack : public GD::Command 
	{
	public:
		Attack() = default;
		~Attack() = default;

		void Execute(GD::GameObject& gameObject) override;
	};

}
