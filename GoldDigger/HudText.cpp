#include "GoldDiggerPCH.h"

#include "HudText.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "GameObject.h"

GD::HudText::HudText(const std::string&& text, const std::string&& font, GD::RenderMode mode, SDL_Color color)
	: m_NeedsUpdate{ true }
	, m_Text{ text }
	, m_Font{ nullptr }
	, m_Texture{ nullptr }
	, m_Color{ color }
	, m_Mode{ mode }
{ 
	m_Font = ResourceManager::GetInstance().GetFont(font);
	if ( m_Font == nullptr ) 
		throw std::runtime_error(std::string("HudTextFont: Font wasn't loaded"));
}

void GD::HudText::Initialize() 
{
	
}

void GD::HudText::Update( float /*deltatime*/ )
{
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

void GD::HudText::Render() const
{
	if (m_Texture != nullptr)
	{
		const Transform transform = m_GameObject->GetTransform();
		Renderer::GetInstance().RenderTexture(m_Texture, transform, m_Mode);
	}
}

void GD::HudText::SetText(const std::string& text)
{
	m_Text = text;
	m_NeedsUpdate = true;
}

void GD::HudText::SetColor(int r, int g, int b) 
{
	m_Color = {Uint8(r), Uint8(g), Uint8(b)};
}