#include "GoldDiggerPCH.h"
#include "Texture.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "GameObject.h"

GD::Texture::Texture(std::string&& textureName)
	: m_Name{ textureName }
{

}

GD::Texture::~Texture()
{

}

void GD::Texture::Initialize() 
{
	m_Texture = ResourceManager::GetInstance().GetTexture(m_Name);
}

void GD::Texture::Update( float /*deltaTime*/ )
{

}

void GD::Texture::Render() const
{
	//const auto pos = mTransform.GetPosition();
	Renderer::GetInstance().RenderTexture(m_Texture, gameObject->GetPosition().x, gameObject->GetPosition().y);
}