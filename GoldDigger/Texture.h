#pragma once
#include "BaseComponent.h"
#include "Structs.h"

struct SDL_Texture;

namespace GD 
{
	class Texture : public BaseComponent
	{
	public:
		Texture(std::string&& textureName, GD::RenderMode mode = GD::RenderMode::corner);
		~Texture();

		void Initialize() override;
		void Update( float deltaTime ) override;
		void Render() const override;
	
	private:

		SDL_Texture* m_Texture;
		std::string m_Name;
		GD::RenderMode m_Mode;
	};
}



