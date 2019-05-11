#include "GoldDiggerPCH.h"
#include "Renderer.h"
#include <SDL.h>
#include "SceneManager.h"
#include "ResourceManager.h"

void GD::Renderer::Init(SDL_Window * window, float gameScale)
{
	mRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	m_GameScale = gameScale;
	if (mRenderer == nullptr)
	{
		throw std::runtime_error(std::string("SDL_CreateRenderer Error: ") + SDL_GetError());
	}
}

void GD::Renderer::Render( float )
{
	SDL_RenderClear(mRenderer);

	SceneManager::GetInstance().Render();

	SDL_RenderPresent(mRenderer);
}

void GD::Renderer::Destroy()
{
	if (mRenderer != nullptr)
	{
		SDL_DestroyRenderer(mRenderer);
		mRenderer = nullptr;
	}
}

void GD::Renderer::RenderTexture(SDL_Texture* texture, const float xPos, const float yPos, 
	const float xScale, const float yScale, GD::RenderMode mode) const
{
	SDL_Rect dst;
	dst.x = static_cast<int>(xPos * m_GameScale);
	dst.y = static_cast<int>(yPos * m_GameScale);
	SDL_QueryTexture(texture, nullptr, nullptr, &dst.w, &dst.h);
	dst.w *= static_cast<int>(m_GameScale * xScale);
	dst.h *= static_cast<int>(m_GameScale * yScale);

	if (mode == RenderMode::center) 
	{
		dst.x -= static_cast<int>(dst.w / 2.f);
		dst.y -= static_cast<int>(dst.h / 2.f);
	}
	SDL_RenderCopy(GetSDLRenderer(), texture, nullptr, &dst);
}

void GD::Renderer::RenderTexture(SDL_Texture* texture, const Vector2& pos, 
	const Vector2& scale, GD::RenderMode mode) const
{
	RenderTexture(texture, pos.x, pos.y, scale.x, scale.y, mode);
}

void GD::Renderer::RenderTexture(SDL_Texture* texture, 
	const Transform& transform, GD::RenderMode mode) const
{
	RenderTexture(texture, transform.pos.x, transform.pos.y, transform.scale.x, transform.scale.y, mode);
}