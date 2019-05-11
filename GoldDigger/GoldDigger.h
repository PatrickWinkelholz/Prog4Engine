#pragma once
#include "Structs.h"

struct SDL_Window;

namespace GD
{
	class GoldDiggerGame;
	class GoldDigger
	{
	private:

		SDL_Window* window{};
		GoldDiggerGame* m_Game;

		void Initialize();
		void Cleanup();

	public:
		GoldDigger(GoldDiggerGame* game);
		~GoldDigger() = default;
		GoldDigger( GoldDigger& ) = delete;
		GoldDigger( GoldDigger&& ) = delete;
		GoldDigger& operator=( GoldDigger& ) = delete;
		GoldDigger& operator=( GoldDigger&& ) = delete;

		void Run();
	};
}