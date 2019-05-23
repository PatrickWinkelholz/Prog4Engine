#include "GoldDiggerPCH.h"
#include "HudText.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "GameObject.h"

GD::HudText::HudText(Texture* texture, const std::string&& text, const std::string&& font, const SDL_Color& color)
	: m_NeedsUpdate{ true }
	, m_Text{ text }
	, m_Font{ nullptr }
	, m_Color{ color }
	, m_Texture{ texture }
{ 
	m_Font = ResourceManager::GetInstance().GetFont(font);
	if (!m_Font) 
	{
		std::cout << "ERROR: HudTextFont: '" << font << "' wasn't loaded!" << std::endl;
		return;
	}
}

void GD::HudText::Initialize() 
{
	
}

void GD::HudText::Update( float /*deltatime*/ )
{
	if (m_NeedsUpdate)
	{
		const auto surf = TTF_RenderText_Blended(m_Font, m_Text.c_str(), m_Color);
		if (!surf) 
		{
			std::cout << "ERROR: Render text: '" << m_Text << "' failed: " << SDL_GetError() << std::endl;
			return;
		}	

		m_Texture->SDLTexture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
		if (!m_Texture->SDLTexture) 
		{
			std::cout << "ERROR: Create text: '" << m_Text << "' from surface failed:" << SDL_GetError() << std::endl;
			return;
		}

		SDL_FreeSurface(surf);

		int w, h;
		SDL_QueryTexture(m_Texture->SDLTexture, nullptr, nullptr, &w, &h);
		m_Texture->sourceRect.botRight.x = static_cast<float>(w);
		m_Texture->sourceRect.botRight.y = static_cast<float>(h);

		m_NeedsUpdate = false;
	}
}

void GD::HudText::SetText(const std::string& text)
{
	SetText( text.c_str() );
}

void GD::HudText::SetText(const std::string&& text) 
{
	m_Text = text;
	m_NeedsUpdate = true;
}

void GD::HudText::SetColor(int r, int g, int b) 
{
	m_Color = {Uint8(r), Uint8(g), Uint8(b)};
	m_NeedsUpdate = true;
}