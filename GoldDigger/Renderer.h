#pragma once
#include "Singleton.h"
#include <map>

struct SDL_Window;
struct SDL_Renderer;
struct SDL_Texture;

namespace GD
{
	class Renderer final : public Singleton<Renderer>
	{
		SDL_Renderer* mRenderer = nullptr;

	public:
		void Init(SDL_Window* window);
		void Render( float lag );
		void Destroy();

		void RenderTexture(SDL_Texture* texture, const float x, const float y) const;
		void RenderTexture(SDL_Texture* texture, float x, float y, float width, float height) const;

		SDL_Renderer* GetSDLRenderer() const { return mRenderer; }
	};
}

