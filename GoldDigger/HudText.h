#pragma once
#include "BaseComponent.h"
#include <string>
#include <SDL.h>
#include <SDL_ttf.h>
#include "Structs.h"

namespace GD
{
	class HudText : public BaseComponent
	{
	public:
		void Initialize() override;
		void Update( float deltaTime ) override;
		void Render() const override;

		void SetText(const std::string& text);
		void SetColor(int r, int g, int b);

		HudText(const std::string&& text, const std::string&& font, 
			GD::RenderMode mode = GD::RenderMode::corner, SDL_Color color = {255, 255, 255});

		~HudText() = default;
		HudText(const HudText& other) = delete;
		HudText(HudText&& other) = delete;
		HudText& operator=(const HudText& other) = delete;
		HudText& operator=(HudText&& other) = delete;
	
	protected:

		bool m_NeedsUpdate;
		std::string m_Text;
		TTF_Font* m_Font;
		SDL_Texture* m_Texture;
		SDL_Color m_Color;
		RenderMode m_Mode;
	};
}
