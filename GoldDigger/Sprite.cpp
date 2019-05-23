#include "GoldDiggerPCH.h"
#include "Sprite.h"
#include "structs.h"
#include "ResourceManager.h"

void GD::Sprite::Initialize()
{
	m_Texture->SDLTexture = ResourceManager::GetInstance().GetTexture(m_Name);
	int w, h;
	SDL_QueryTexture(m_Texture->SDLTexture, nullptr, nullptr, &w, &h);
	m_Texture->sourceRect.botRight.x = static_cast<float>( w );
	m_Texture->sourceRect.botRight.y = static_cast<float>( h );

	PlayAnimation(m_ActiveAnimation);
}

void GD::Sprite::Update(float deltaTime)
{
	if (m_Timer < 0)
		return;

	m_Timer += deltaTime;
	Animation anim = m_Animations[m_ActiveAnimation];
	if (m_Timer >= anim.frameTime && anim.frameTime > 0)
	{
		m_Timer -= anim.frameTime;
		m_Texture->sourceRect.topLeft.x += anim.GetFrameWidth();
		m_Texture->sourceRect.botRight.x += anim.GetFrameWidth();
		if (m_Texture->sourceRect.topLeft.x >= anim.allFrames.botRight.x - 0.001f) 
		{
			if (anim.loop)
			{
				ResetAnimation();
			}
			else
				m_Timer = -1.f;
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
		ResetAnimation();
	}
}

void GD::Sprite::ResetAnimation() 
{
	Animation anim = m_Animations[m_ActiveAnimation];
	m_Texture->sourceRect.topLeft = anim.allFrames.topLeft;
	m_Texture->sourceRect.botRight.x = anim.allFrames.topLeft.x + anim.GetFrameWidth();
	m_Texture->sourceRect.botRight.y = anim.allFrames.botRight.y;
}
