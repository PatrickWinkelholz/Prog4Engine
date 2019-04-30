#pragma once
#include "BaseComponent.h"
//#include "HudText.h"

namespace engine 
{
	class HudText;
	class FPSCounter : public BaseComponent
	{
	public:

		void Initialize() override;
		void Update(float deltaTime) override;
		void Render() const override;

		FPSCounter();
		~FPSCounter();
		FPSCounter(const FPSCounter& other) = delete;
		FPSCounter(FPSCounter&& other) = delete;
		FPSCounter& operator=(const FPSCounter& other) = delete;
		FPSCounter& operator=(FPSCounter&& other) = delete;

	private:
		int m_Frames;
		float m_SecondCounter;
		HudText* m_HudText;
	};
}


