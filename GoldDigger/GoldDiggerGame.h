#pragma once

namespace GD 
{
	class GoldDiggerGame
	{
	public:
		GoldDiggerGame() = default;
		virtual ~GoldDiggerGame() = default;

		GoldDiggerGame(GoldDiggerGame&) = delete;
		GoldDiggerGame(GoldDiggerGame&&) = delete;
		GoldDiggerGame& operator=(GoldDiggerGame&) = delete;
		GoldDiggerGame&& operator=(GoldDiggerGame&&) = delete;

		virtual void LoadGame() = 0;
		virtual void LoadResources() = 0;
	};
}


