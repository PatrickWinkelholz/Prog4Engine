#pragma once
#include "BaseComponent.h"
#include "Commands.h"
#include "structs.h"

namespace GD
{
	struct Texture;

	class MenuButton : public BaseComponent
	{
		friend CycleButtons;
		friend ExecuteCurrentButton;

	public:
		MenuButton(GD::Texture* off, GD::Texture* on, Command* command, float activeScaleFactor = 1.3f);
		~MenuButton() { if (m_Command) delete m_Command; };

		void Initialize() override;
		void Update(float deltaTime) override;

	private:
		void ExecuteCommand();
		void GainFocus();
		void LooseFocus();

		bool m_Focused;
		float m_ActiveScaleFactor;
		Texture* m_OffTexture;
		Texture* m_OnTexture;
		Command* m_Command;
		MenuButton* m_NextButton;
		MenuButton* m_PrevButton;
		Vector2 m_OriginalScale;

		static MenuButton* s_ActiveButton;
	};
}


