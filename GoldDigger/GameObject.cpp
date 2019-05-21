#include "GoldDiggerPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "BaseComponent.h"
#include <SDL.h>

GD::GameObject::GameObject() 
	: m_Components{ }
	, m_Transform{ {0, 0}, {1.f, 1.f}, 0 }
{

}

GD::GameObject::~GameObject() 
{
	for (BaseComponent* component : m_Components) 
		delete component;
	for (Texture* texture : m_Textures)
		delete texture;
};

void GD::GameObject::Initialize() 
{
	for (BaseComponent* component : m_Components) 
		component->Initialize();
}

void GD::GameObject::Update( float deltaTime )
{
	for (BaseComponent* component : m_Components) 
		component->Update(deltaTime);
}

void GD::GameObject::Render() const
{
	for (const Texture* texture : m_Textures) 
		if (texture->enabled)
			Renderer::GetInstance().RenderTexture(texture->SDLTexture, m_Transform, texture->mode);
}

void GD::GameObject::SetPosition(float x, float y, const Grid & grid)
{
	if (grid.cols > 0 && grid.rows > 0)
	{
		m_Transform.pos.x = grid.bounds.topLeft.x + grid.tileDimensions.x * x;
		m_Transform.pos.y = grid.bounds.topLeft.y + grid.tileDimensions.y * y;
	}
	else 
	{
		m_Transform.pos.x = x;
		m_Transform.pos.y = y;
	}
}

void GD::GameObject::AddComponent(BaseComponent* component) 
{
	component->m_GameObject = this;
	m_Components.push_back(component);
}

GD::Texture* GD::GameObject::CreateTexture(RenderMode mode, bool enabled) 
{
	m_Textures.push_back(new Texture{nullptr, mode, enabled});
	return m_Textures[m_Textures.size()-1];
}