#pragma once
#include "BaseComponent.h"
#include "Structs.h"
#include <SDL_ttf.h>
//#include <string>

namespace GD
{
	class HudText : public BaseComponent
	{
	public:
		HudText(Texture* texture, const std::string&& text, const std::string&& font, SDL_Color color = {255, 255, 255});
		~HudText() = default;
		HudText(const HudText& other) = delete;
		HudText(HudText&& other) = delete;
		HudText& operator=(const HudText& other) = delete;
		HudText& operator=(HudText&& other) = delete;
	
		void Initialize() override;
		void Update(float deltaTime) override;

		void SetText(const std::string& text);
		void SetText(const std::string&& text);
		void SetColor(int r, int g, int b);

	private:
		bool m_NeedsUpdate;
		std::string m_Text;
		TTF_Font* m_Font;
		SDL_Color m_Color;
		Texture* m_Texture;
	};
}
