#include "GoldDiggerPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "BaseComponent.h"

engine::GameObject::GameObject() 
	: m_Components{ }
	, m_Transform{ 0, 0, 0}
{

}

engine::GameObject::~GameObject() 
{
	for (BaseComponent* c : m_Components) 
	{
		delete c;
	}
};

void engine::GameObject::Update( float deltaTime )
{
	for (BaseComponent* c : m_Components) 
	{
		c->Update(deltaTime);
	}
}

void engine::GameObject::Render() const
{
	for (BaseComponent* c : m_Components) 
	{
		c->Render();
	}
	//const auto pos = mTransform.GetPosition();
	//Renderer::GetInstance().RenderTexture(*mTexture, pos.x, pos.y);
}

void engine::GameObject::AddComponent(BaseComponent* component) 
{
	m_Components.push_back(component);
	component->gameObject = this;
}

//void engine::GameObject::SetTexture(const std::string& filename)
//{
//	mTexture = ResourceManager::GetInstance().LoadTexture(filename);
//}

void engine::GameObject::SetPosition(float x, float y)
{
	m_Transform.x = x;
	m_Transform.y = y;
}

const engine::Transform& engine::GameObject::GetPosition() const
{
	return m_Transform;
}
