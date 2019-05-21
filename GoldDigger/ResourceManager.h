#pragma once
#include "Singleton.h"
#include <map>
#include <SDL_ttf.h>

struct SDL_Texture;

namespace GD
{
	class ResourceManager final : public Singleton<ResourceManager>
	{
		std::string mDataPath;

	public:
		ResourceManager() = default;

		void Init(std::string&& data);

		void LoadTexture(const std::string& file);
		void LoadFont(const std::string& file, unsigned int size);
		void ReleaseAll();

		SDL_Texture* GetTexture(const std::string& textureName);
		SDL_Texture* GetTexture(const std::string&& textureName);
		TTF_Font* GetFont(const std::string& fontName);
		TTF_Font* GetFont(const std::string&& fontName);
	
	private:
		std::map<std::string, SDL_Texture*> m_Textures;
		std::map<std::string, TTF_Font*> m_Fonts;
	};
}
