#include "MiniginPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "BaseComponent.h"

dae::GameObject::GameObject() 
	: m_Components{ }
	, m_Transform{ 0, 0, 0}
{

}

dae::GameObject::~GameObject() 
{
	for (BaseComponent* c : m_Components) 
	{
		delete c;
	}
};

void dae::GameObject::Update( float deltaTime )
{
	for (BaseComponent* c : m_Components) 
	{
		c->Update(deltaTime);
	}
}

void dae::GameObject::Render() const
{
	for (BaseComponent* c : m_Components) 
	{
		c->Render();
	}
	//const auto pos = mTransform.GetPosition();
	//Renderer::GetInstance().RenderTexture(*mTexture, pos.x, pos.y);
}

void dae::GameObject::AddComponent(BaseComponent* component) 
{
	m_Components.push_back(component);
	component->gameObject = this;
}

//void dae::GameObject::SetTexture(const std::string& filename)
//{
//	mTexture = ResourceManager::GetInstance().LoadTexture(filename);
//}

void dae::GameObject::SetPosition(float x, float y)
{
	m_Transform.x = x;
	m_Transform.y = y;
}

const dae::Transform& dae::GameObject::GetPosition() const
{
	return m_Transform;
}
