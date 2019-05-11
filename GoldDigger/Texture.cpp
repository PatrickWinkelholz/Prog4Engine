#include "GoldDiggerPCH.h"
#include "Texture.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "GameObject.h"

GD::Texture::Texture(std::string&& textureName, GD::RenderMode mode)
	: m_Name{ textureName }
	, m_Mode{ mode }
{

}

GD::Texture::~Texture()
{

}

void GD::Texture::Initialize() 
{
	m_Texture = ResourceManager::GetInstance().GetTexture(m_Name);
	if (!m_Texture)
		std::cout << "ERROR: texture not found: " << m_Name << std::endl;
}

void GD::Texture::Update( float /*deltaTime*/ )
{

}

void GD::Texture::Render() const
{
	const Transform transform = m_GameObject->GetTransform();
	Renderer::GetInstance().RenderTexture(m_Texture, transform, m_Mode);
}