#include "GoldDiggerPCH.h"

#include "HudText.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "GameObject.h"

engine::HudText::HudText(const std::string&& text, const std::string&& font, SDL_Color color) 
	: m_NeedsUpdate(true)
	, m_Text(text)
	, m_Font(nullptr)
	, m_Texture(nullptr)
	, m_Color(color)
{ 
	m_Font = ResourceManager::GetInstance().GetFont(font);
	if ( m_Font == nullptr ) 
		throw std::runtime_error(std::string("HudTextFont: Font wasn't loaded"));
}

void engine::HudText::Update( float deltaTime )
{
	(deltaTime); //not referenced
	if (m_NeedsUpdate)
	{
		const auto surf = TTF_RenderText_Blended(m_Font, m_Text.c_str(), m_Color);
		if (surf == nullptr) 
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		m_Texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
		if (m_Texture == nullptr) 
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_FreeSurface(surf);
	}
}

void engine::HudText::Render() const
{
	if (m_Texture != nullptr)
	{
		const auto pos = gameObject->GetPosition();
		Renderer::GetInstance().RenderTexture(m_Texture, pos.x, pos.y);
	}
}

void engine::HudText::SetText(const std::string& text)
{
	m_Text = text;
	m_NeedsUpdate = true;
}

void engine::HudText::SetColor(int r, int g, int b) 
{
	m_Color = {Uint8(r), Uint8(g), Uint8(b)};
}