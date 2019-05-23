#include "GoldDiggerPCH.h"
#include "Sprite.h"
#include "structs.h"
#include "ResourceManager.h"

void GD::Sprite::Initialize()
{
	m_Texture->SDLTexture = ResourceManager::GetInstance().GetTexture(m_Name);
	PlayAnimation(m_ActiveAnimation);
}

void GD::Sprite::Update(float deltaTime)
{
	if (m_Animations.size() != 0)
	{
		m_Timer += deltaTime;
		Animation anim = m_Animations[m_ActiveAnimation];
		if (m_Timer >= anim.frameTime && anim.frameTime > 0)
		{
			m_Timer -= anim.frameTime;
			m_Texture->sourceRect.topLeft.x += m_Texture->sourceRect.width;
			m_Texture->sourceRect.botRight.x += m_Texture->sourceRect.width;
			if (m_Texture->sourceRect.topLeft.x >= anim.allFrames.botRight.x - 0.001f) 
			{
				m_Texture->sourceRect.topLeft.x = anim.allFrames.topLeft.x;
				m_Texture->sourceRect.botRight.x = anim.allFrames.botRight.x;
			}
		}
	}
}

void GD::Sprite::AddAnimation(unsigned int id, const Animation & animation)
{
	m_Animations[id] = animation;
}

void GD::Sprite::PlayAnimation(unsigned int id)
{
	if (m_Animations.size() != 0)
	{
		m_Timer = 0;
		m_ActiveAnimation = id;
		Animation anim = m_Animations[m_ActiveAnimation];
		m_Texture->sourceRect.topLeft = anim.allFrames.topLeft;
		m_Texture->sourceRect.botRight = anim.allFrames.botRight;
		m_Texture->sourceRect.width = anim.allFrames.width / static_cast<float>(anim.nrFrames);
		m_Texture->sourceRect.height = anim.allFrames.height;
	}
}
