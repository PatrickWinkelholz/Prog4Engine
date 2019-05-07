#include "GoldDiggerPCH.h"
#include "FPSCounter.h"
#include "HudText.h"
#include <SDL.h>
#include "GameObject.h"

GD::FPSCounter::FPSCounter()
	: m_Frames{ 0 }
	, m_SecondCounter{ 0 }
{
}

GD::FPSCounter::~FPSCounter()
{

}

void GD::FPSCounter::Initialize() 
{
	m_HudText = new HudText("FPS", "Lingua", SDL_Color{ 255, 255, 0 });
	gameObject->AddComponent(m_HudText);
	m_HudText->Initialize();
}

void GD::FPSCounter::Update(float deltaTime)
{
	m_Frames++;
	m_SecondCounter += deltaTime;
	if (m_SecondCounter >= 1.f) 
	{
		m_HudText->SetText(std::to_string(m_Frames) + " FPS");
		m_SecondCounter = 0;
		m_Frames = 0;
	}
}

void GD::FPSCounter::Render() const
{
}