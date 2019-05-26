#pragma once
#include <Observer.h>
#include <Structs.h>

namespace GD 
{
	class Sprite;
	class HudText;
	class Entity;
}

namespace DD 
{
	class ScoreDisplay : public GD::Observer
	{
	public:
		ScoreDisplay(GD::HudText* hudText, const GD::Grid& grid) 
			: m_HudText{ hudText } 
			, m_Grid{ grid }
		{};
		~ScoreDisplay() = default;

		void OnNotify(GD::Entity* caller, unsigned int event) override;

	private:
		int m_Score;
		GD::HudText* m_HudText;
		GD::Grid m_Grid;
	};

	class LifeDisplay : public GD::Observer
	{
	public:
		LifeDisplay(GD::Texture* texture, int nrLives) 
			: m_Texture{ texture } 
			, m_NrLives{ nrLives } 
			, m_LifeWidth{ 0 }
		{};
		~LifeDisplay() = default;

		void OnNotify(GD::Entity* caller, unsigned int event) override;
	
	private:
		GD::Texture* m_Texture;
		int m_NrLives;
		float m_LifeWidth;
	};
}
