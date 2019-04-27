#include "MiniginPCH.h"
#include "FPSCounter.h"
#include <SDL.h>

dae::FPSCounter::FPSCounter()
	: HudText("FPS", "Lingua", SDL_Color{255, 255, 0})
	, m_Frames{ 0 }
	, m_SecondCounter{ 0 }
{
}

dae::FPSCounter::~FPSCounter()
{
}

void dae::FPSCounter::Update(float deltaTime)
{
	m_Frames++;
	m_SecondCounter += deltaTime;
	if (m_SecondCounter >= 1.f) 
	{
		SetText(std::to_string(m_Frames) + " FPS");
		m_SecondCounter = 0;
		m_Frames = 0;
	}
	HudText::Update( deltaTime );
}

void dae::FPSCounter::Render() const
{
	HudText::Render();
}