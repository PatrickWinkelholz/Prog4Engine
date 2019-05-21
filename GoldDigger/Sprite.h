#pragma once
#include "BaseComponent.h"

namespace GD 
{
	struct Texture;

	class Sprite : public BaseComponent
	{
	public:
		Sprite(Texture* texture, std::string&& name) 
			: m_Texture{ texture }, m_Name{ name } {};
		~Sprite() = default;

		void Initialize();
		void Update(float deltaTime);

	private:
		std::string m_Name;
		Texture* m_Texture;
	}; 
}
