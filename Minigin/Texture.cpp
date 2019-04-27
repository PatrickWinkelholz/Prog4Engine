#include "MiniginPCH.h"
#include "Texture.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "GameObject.h"

dae::Texture::Texture(std::string&& textureName)
	: m_Name{ textureName }
{
	m_Texture = ResourceManager::GetInstance().GetTexture(textureName);
}

dae::Texture::~Texture()
{

}

void dae::Texture::Update( float deltaTime )
{
	(deltaTime); //not referenced
}

void dae::Texture::Render() const
{
	//const auto pos = mTransform.GetPosition();
	Renderer::GetInstance().RenderTexture(m_Texture, gameObject->GetPosition().x, gameObject->GetPosition().y);
}