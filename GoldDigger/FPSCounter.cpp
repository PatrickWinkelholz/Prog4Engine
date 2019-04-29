#include "GoldDiggerPCH.h"
#include "FPSCounter.h"
#include "HudText.h"
#include <SDL.h>

engine::FPSCounter::FPSCounter()
	: m_Frames{ 0 }
	, m_SecondCounter{ 0 }
{
	m_HudText = new HudText("FPS", "Lingua", SDL_Color{ 255, 255, 0 });
}

engine::FPSCounter::~FPSCounter()
{
	delete m_HudText;
}

void engine::FPSCounter::Update(float deltaTime)
{
	m_Frames++;
	m_SecondCounter += deltaTime;
	if (m_SecondCounter >= 1.f) 
	{
		m_HudText->SetText(std::to_string(m_Frames) + " FPS");
		m_SecondCounter = 0;
		m_Frames = 0;
	}
	m_HudText->Update( deltaTime );
}

void engine::FPSCounter::Render() const
{
	m_HudText->Render();
}