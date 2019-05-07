#include "GoldDiggerPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "BaseComponent.h"

GD::GameObject::GameObject() 
	: m_Components{ }
	, m_Transform{ 0, 0, 0}
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
	component->gameObject = this;
	m_Components.push_back(component);
}

//void GD::GameObject::SetTexture(const std::string& filename)
//{
//	mTexture = ResourceManager::GetInstance().LoadTexture(filename);
//}

void GD::GameObject::SetPosition(float x, float y)
{
	m_Transform.x = x;
	m_Transform.y = y;
}

const GD::Transform& GD::GameObject::GetPosition() const
{
	return m_Transform;
}
