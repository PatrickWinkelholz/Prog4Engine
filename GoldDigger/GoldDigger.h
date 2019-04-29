#pragma once

struct SDL_Window;

namespace engine
{
	class GoldDigger
	{
		const int msPerFrame = 16; //16 for 60 fps, 33 for 30 fps
		SDL_Window* window{};
	public:
		void Initialize();
		void LoadGame();
		void LoadResources();
		void Cleanup();
		void Run();
	};
}