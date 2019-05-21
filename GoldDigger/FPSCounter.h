#pragma once
#include "BaseComponent.h"
#include "HudText.h"

namespace GD
{
	class FPSCounter : public BaseComponent
	{
	public:

		void Initialize() override;
		void Update(float deltaTime) override;

		FPSCounter(HudText* hudText) : m_Frames{ 0 }, m_SecondCounter{ 0 }, m_HudText{ hudText } {};
		~FPSCounter() = default;
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


