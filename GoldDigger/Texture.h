#pragma once
#include "BaseComponent.h"

struct SDL_Texture;

namespace engine 
{
	class Texture : public BaseComponent
	{
	public:
		Texture(std::string&& textureName);
		~Texture();

		void Update( float deltaTime ) override;
		void Render() const override;
	
	private:

		SDL_Texture* m_Texture;
		std::string m_Name;
	};
}



