#include "GoldDiggerPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "BaseComponent.h"

GD::GameObject::GameObject() 
	: m_Components{ }
	, m_Transform{ {0, 0}, {1.f, 1.f}, 0 }
{

}

GD::GameObject::~GameObject() 
{
	for (BaseComponent* c : m_Components) 
	{
		delete c;
	}
};

void GD::GameObject::Initialize() 
{
	for (BaseComponent* c : m_Components) 
	{
		c->Initialize();
	}
}

void GD::GameObject::Update( float deltaTime )
{
	for (BaseComponent* c : m_Components) 
	{
		c->Update(deltaTime);
	}
}

void GD::GameObject::Render() const
{
	for (BaseComponent* c : m_Components) 
	{
		c->Render();
	}
	//const auto pos = mTransform.GetPosition();
	//Renderer::GetInstance().RenderTexture(*mTexture, pos.x, pos.y);
}

void GD::GameObject::AddComponent(BaseComponent* component) 
{
	component->m_GameObject = this;
	m_Components.push_back(component);
}

void GD::GameObject::SetPosition(float x, float y)
{
	m_Transform.pos.x = x;
	m_Transform.pos.y = y;
}

void GD::GameObject::SetScale(float x, float y)
{
	m_Transform.scale.x = x;
	m_Transform.scale.y = y;
}

void GD::GameObject::SetPosition( const GD::Vector2& pos ) 
{
	m_Transform.pos = pos;
}

void GD::GameObject::SetScale(const GD::Vector2& scale) 
{
	m_Transform.scale = scale;
}

void GD::GameObject::SetTransform(const Transform& transform)
{
	m_Transform = transform;
}

const GD::Transform & GD::GameObject::GetTransform() const
{
	return m_Transform;
}

const GD::Vector2& GD::GameObject::GetPosition() const
{
	return m_Transform.pos;
}

const GD::Vector2& GD::GameObject::GetScale() const
{
	return m_Transform.scale;
}
