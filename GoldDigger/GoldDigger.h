#pragma once

struct SDL_Window;

namespace GD
{
	class GoldDiggerGame;
	class GoldDigger
	{
		const int msPerFrame = 16; //16 for 60 fps, 33 for 30 fps
		SDL_Window* window{};
	public:
		void Initialize();
		void Cleanup();
		void Run();
		void SetGame(GoldDiggerGame* game);

		GoldDiggerGame* m_Game;
	};
}