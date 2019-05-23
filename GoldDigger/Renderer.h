#pragma once
#include "Singleton.h"
#include <vector>
#include "Structs.h"

struct SDL_Window;
struct SDL_Renderer;
struct SDL_Texture;

namespace GD
{
	class Renderer final : public Singleton<Renderer>
	{
	public:
		void Init(SDL_Window* window, float gameScale);
		void Render( float lag );
		void Destroy();

		void RenderTexture(const Texture& texture, const float xPos, const float yPos,
			const float xScale = 1.f, const float yScale = 1.f) const;
		
		void RenderTexture(const Texture& texture, const Vector2& pos, 
			const Vector2& scale = {1.f, 1.f}) const;

		void RenderTexture(const Texture& texture, const Transform& transform) const;

		SDL_Renderer* GetSDLRenderer() const { return m_Renderer; }

	private:
		SDL_Renderer* m_Renderer = nullptr;
		float m_GameScale;

	};
}

