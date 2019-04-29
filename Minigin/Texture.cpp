#include "MiniginPCH.h"
#include "Texture.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "GameObject.h"

engine::Texture::Texture(std::string&& textureName)
	: m_Name{ textureName }
{
	m_Texture = ResourceManager::GetInstance().GetTexture(textureName);
}

engine::Texture::~Texture()
{

}

void engine::Texture::Update( float deltaTime )
{
	(deltaTime); //not referenced
}

void engine::Texture::Render() const
{
	//const auto pos = mTransform.GetPosition();
	Renderer::GetInstance().RenderTexture(m_Texture, gameObject->GetPosition().x, gameObject->GetPosition().y);
}