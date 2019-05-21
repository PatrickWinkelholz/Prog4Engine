#pragma once
#include <GoldDiggerGame.h>
#include "DigDugStructs.h"

namespace DD 
{
	class DigDug : public GD::GoldDiggerGame
	{
		friend class StartGame; //Allow the start game command to change the GameMode

	public:

		DigDug();
		~DigDug();

		DigDug(DigDug&) = delete;
		DigDug(DigDug&&) = delete;
		DigDug& operator=(DigDug&) = delete;
		DigDug&& operator=(DigDug&&) = delete;

		void Initialize() override;

		static const GD::Vector2 GetDimensions() { return m_Dimensions; };
		static const GD::Grid GetGrid() { return m_Grid; };
		static const GameMode GetGameMode() { return m_GameMode; };

	private:

		void LoadResources();

		static GameMode m_GameMode;
		static const GD::Vector2 m_Dimensions;
		static const int m_Rows;
		static const int m_Cols;
		static const GD::Vector2 m_TileDimensions;
		static const GD::Grid m_Grid;
	};
}
