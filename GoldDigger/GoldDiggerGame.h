#pragma once
#include "Structs.h"

namespace GD 
{
	class GoldDiggerGame
	{
	public:
		GoldDiggerGame(Vector2 dimensions = { 100.f, 100.f }, int msPerFrame = 16, float gameScale = 3.f, float msPerUpdate = 0.02f)
			: m_Dimensions{ dimensions }
			, m_MsPerFrame{ msPerFrame }
			, m_MsPerUpdate{ msPerUpdate }
			, m_GameScale{ gameScale }
		{};
		virtual ~GoldDiggerGame() = default;

		GoldDiggerGame(GoldDiggerGame&) = delete;
		GoldDiggerGame(GoldDiggerGame&&) = delete;
		GoldDiggerGame& operator=(GoldDiggerGame&) = delete;
		GoldDiggerGame&& operator=(GoldDiggerGame&&) = delete;

		virtual void Initialize() = 0;

		Vector2 m_Dimensions;
		int m_MsPerFrame;
		float m_GameScale;
		float m_MsPerUpdate;
	};
}


