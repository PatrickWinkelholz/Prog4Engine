#pragma once

namespace GD 
{
	class GameObject;

	class BaseComponent
	{
	public:

		virtual void Initialize() = 0;
		virtual void Update( float deltaTime ) = 0;

		BaseComponent() = default;
		virtual ~BaseComponent() = default;
		BaseComponent(const BaseComponent& other) = delete;
		BaseComponent(BaseComponent&& other) = delete;
		BaseComponent& operator=(const BaseComponent& other) = delete;
		BaseComponent& operator=(BaseComponent&& other) = delete;
	
		GameObject* m_GameObject{ nullptr };
	};
}


