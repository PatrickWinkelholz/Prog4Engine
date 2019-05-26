#include "pch.h"
#include "DigDugObservers.h"
#include "DigDugStructs.h"
#include <HudText.h>
#include <string>
#include <Entity.h>
#include "DigDugAgents.h"
#include <GameObject.h>

void DD::ScoreDisplay::OnNotify(GD::Entity* caller, unsigned int id) 
{
	EventID eventID = static_cast<EventID>(id);

	if (eventID == EventID::EnemyPumped) 
	{
		int multiplier = 1;
		if (typeid(*caller->GetAgent()) == typeid(FygarAgent))
			multiplier = 2;

		int score = 200;
		for (int i{ 1 }; i < 4; i++) 
		{
			if (caller->m_GameObject->GetPosition().y > m_Grid.bounds.topLeft.y + m_Grid.GetDimensions().y / 4.f * float(i))
				score += 100;
		}
		m_Score += score * multiplier;
	}
	else if (eventID == EventID::EnemyCrushed) 
	{
		m_Score += 1000;
	}

	std::string score{ std::to_string(m_Score) };
	while (score.length() < 8) 
	{
		score = "0" + score;
	}
	m_HudText->SetText(score);
}

void DD::LifeDisplay::OnNotify(GD::Entity* /*caller*/, unsigned int eventID)
{
	if (eventID == static_cast<unsigned int>(EventID::PLayerDied)) 
	{
		if (m_LifeWidth == 0)
			m_LifeWidth = m_Texture->sourceRect.GetWidth() / float(m_NrLives);

		m_Texture->sourceRect.botRight.x -= m_LifeWidth;
		m_NrLives--;
	}
}