#include "GoldDiggerPCH.h"
#include "FPSCounter.h"

void GD::FPSCounter::Initialize() 
{

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