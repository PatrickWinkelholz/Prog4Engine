#pragma once
#include "BaseComponent.h"
#include <map>
#include "Structs.h"

namespace GD 
{
	class Sprite : public BaseComponent
	{
	public:
		Sprite(Texture* texture, std::string&& name) 
			: m_Texture{ texture }
			, m_Name{ name } 
			, m_Animations{}
			, m_ActiveAnimation{0}
		{};
		~Sprite() = default;

		void Initialize();
		void Update(float deltaTime);
		void AddAnimation(unsigned int id, const Animation& animation);
		void PlayAnimation(unsigned int id);

	private:
		std::string m_Name;
		Texture* m_Texture;
		std::map<unsigned int, Animation> m_Animations;
		unsigned int m_ActiveAnimation;
		float m_Timer;
	}; 
}
