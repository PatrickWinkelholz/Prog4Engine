#pragma once
#include "Singleton.h"
#include <map>
#include "Structs.h"

struct SDL_Window;
struct SDL_Renderer;
struct SDL_Texture;

namespace GD
{
	class Renderer final : public Singleton<Renderer>
	{
	private:
		SDL_Renderer* mRenderer = nullptr;
		float m_GameScale;

	public:
		void Init(SDL_Window* window, float gameScale);
		void Render( float lag );
		void Destroy();

		void RenderTexture(SDL_Texture* texture, const float xPos, const float yPos, 
			const float xScale = 1.f, const float yScale = 1.f, GD::RenderMode mode = GD::RenderMode::corner) const;
		
		void RenderTexture(SDL_Texture* texture, const Vector2& pos, const Vector2& scale = {1.f, 1.f},
			GD::RenderMode mode = GD::RenderMode::corner) const;

		void RenderTexture(SDL_Texture* texture, const Transform& transform, 
			GD::RenderMode mode = GD::RenderMode::corner) const;

		SDL_Renderer* GetSDLRenderer() const { return mRenderer; }
	};
}

