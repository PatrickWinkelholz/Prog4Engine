#pragma once

namespace engine 
{
	class GameObject;

	class BaseComponent
	{
	public:

		virtual void Initialize() = 0;
		virtual void Update( float deltaTime ) = 0;
		virtual void Render() const = 0;

		BaseComponent() = default;
		virtual ~BaseComponent() = default;
		BaseComponent(const BaseComponent& other) = delete;
		BaseComponent(BaseComponent&& other) = delete;
		BaseComponent& operator=(const BaseComponent& other) = delete;
		BaseComponent& operator=(BaseComponent&& other) = delete;
		
		GameObject* gameObject{ nullptr };
	};
}


