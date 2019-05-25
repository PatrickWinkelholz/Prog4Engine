#include "GoldDiggerPCH.h"
#include "Renderer.h"
#include <SDL.h>
#include "SceneManager.h"
#include "ResourceManager.h"

void GD::Renderer::Init(SDL_Window * window, float gameScale)
{
	m_Renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	m_GameScale = gameScale;
	if (m_Renderer == nullptr)
	{
		throw std::runtime_error(std::string("SDL_CreateRenderer Error: ") + SDL_GetError());
	}
}

void GD::Renderer::Render( float )
{
	SDL_RenderClear(m_Renderer);

	SceneManager::GetInstance().Render();

	SDL_RenderPresent(m_Renderer);
}

void GD::Renderer::Destroy()
{
	if (m_Renderer)
	{
		SDL_DestroyRenderer(m_Renderer);
		m_Renderer = nullptr;
	}
}

void GD::Renderer::RenderTexture(const Texture& texture, const float xPos, const float yPos, 
	const float xScale, const float yScale) const
{
	if (!texture.enabled)
		return;
	
	SDL_Rect src;
	src.x = static_cast<int>(texture.sourceRect.topLeft.x);
	src.y = static_cast<int>(texture.sourceRect.topLeft.y);
	src.w = static_cast<int>(texture.sourceRect.GetWidth());
	src.h = static_cast<int>(texture.sourceRect.GetHeight());
	
	SDL_Rect dst;
	dst.x = static_cast<int>(xPos * m_GameScale);
	dst.y = static_cast<int>(yPos * m_GameScale);
	dst.w = static_cast<int>(src.w * m_GameScale * xScale);
	dst.h = static_cast<int>(src.h * m_GameScale * yScale);
	
	if (texture.mode == RenderMode::center)
	{
		dst.x -= static_cast<int>(dst.w / 2.f);
		dst.y -= static_cast<int>(dst.h / 2.f);
	}
	else if (texture.mode == RenderMode::centerLeft)
	{
		dst.y -= static_cast<int>(dst.h / 2.f);
	}

	SDL_RenderCopy(GetSDLRenderer(), texture.SDLTexture, texture.sourceRect.GetWidth() != 0 ? &src : nullptr, &dst);
}

void GD::Renderer::RenderTexture(const Texture& texture, const Vector2& pos, 
	const Vector2& scale) const
{
	RenderTexture(texture, pos.x, pos.y, scale.x, scale.y);
}

void GD::Renderer::RenderTexture(const Texture& texture, 
	const Transform& transform) const
{
	RenderTexture(texture, transform.pos.x, transform.pos.y, transform.scale.x, transform.scale.y);
}