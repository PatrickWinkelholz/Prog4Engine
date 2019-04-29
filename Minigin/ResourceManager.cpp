#include "MiniginPCH.h"
#include "ResourceManager.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Renderer.h"

void engine::ResourceManager::Init(std::string&& dataPath)
{
	mDataPath = std::move(dataPath);
	// load support for png and jpg, this takes a while!

	if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG) 
	{
		throw std::runtime_error(std::string("Failed to load support for png's: ") + SDL_GetError());
	}

	if ((IMG_Init(IMG_INIT_JPG) & IMG_INIT_JPG) != IMG_INIT_JPG) 
	{
		throw std::runtime_error(std::string("Failed to load support for jpg's: ") + SDL_GetError());
	}

	if (TTF_Init() != 0) 
	{
		throw std::runtime_error(std::string("Failed to load support for fonts: ") + SDL_GetError());
	}
}

void engine::ResourceManager::LoadTexture(const std::string& file)
{
	std::string fullPath = mDataPath + file;
	SDL_Texture *texture = IMG_LoadTexture(Renderer::GetInstance().GetSDLRenderer(), fullPath.c_str());
	if (texture == nullptr) 
	{
		throw std::runtime_error(std::string("Failed to load texture: ") + SDL_GetError());
	}
	m_Textures[file.substr(0, file.rfind('.'))] = texture;
}

void engine::ResourceManager::LoadFont(const std::string& file, unsigned int size)
{
	TTF_Font* font = TTF_OpenFont((mDataPath + file).c_str(), size);
	if (font == nullptr)
	{
		throw std::runtime_error(std::string("Failed to load font: ") + SDL_GetError());
	}
	m_Fonts[file.substr(0, file.rfind('.'))] = font;
}

void engine::ResourceManager::ReleaseAll() 
{
	for (std::pair<const std::string, TTF_Font *> p : m_Fonts) 
	{
		TTF_CloseFont(p.second);
		m_Fonts.erase(p.first);
	}
	for (std::pair<std::string, SDL_Texture*> p : m_Textures) 
	{
		SDL_DestroyTexture(p.second);
		m_Textures.erase(p.first);
	}
}

SDL_Texture* engine::ResourceManager::GetTexture(const std::string& textureName)
{
	return m_Textures[textureName];
}

TTF_Font* engine::ResourceManager::GetFont(const std::string& fontName)
{
	return m_Fonts[fontName];
}

SDL_Texture* engine::ResourceManager::GetTexture(const std::string&& textureName) 
{
	return m_Textures[textureName];
}

TTF_Font* engine::ResourceManager::GetFont(const std::string&& fontName)
{
	return m_Fonts[fontName];
}
