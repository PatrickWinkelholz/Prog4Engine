#include "GoldDiggerPCH.h"
#include "Texture.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "GameObject.h"

engine::Texture::Texture(std::string&& textureName)
	: m_Name{ textureName }
{

}

engine::Texture::~Texture()
{

}

void engine::Texture::Initialize() 
{
	m_Texture = ResourceManager::GetInstance().GetTexture(m_Name);
}

void engine::Texture::Update( float /*deltaTime*/ )
{

}

void engine::Texture::Render() const
{
	//const auto pos = mTransform.GetPosition();
	Renderer::GetInstance().RenderTexture(m_Texture, gameObject->GetPosition().x, gameObject->GetPosition().y);
}