#pragma once
#include "HudText.h"

namespace engine 
{
	class FPSCounter : public engine::HudText
	{
	public:

		void Update(float deltaTime) override;
		void Render() const override;

		FPSCounter();
		~FPSCounter();

	private:
		int m_Frames;
		float m_SecondCounter;
	};
}


