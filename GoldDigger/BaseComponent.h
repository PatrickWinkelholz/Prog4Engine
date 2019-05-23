#pragma once

namespace GD 
{
	class GameObject;

	class BaseComponent
	{
	public:

		virtual void Initialize() = 0;
		virtual void Update( float deltaTime ) = 0;

		BaseComponent() : m_Enabled(true) {};
		virtual ~BaseComponent() = default;
		BaseComponent(const BaseComponent& other) = delete;
		BaseComponent(BaseComponent&& other) = delete;
		BaseComponent& operator=(const BaseComponent& other) = delete;
		BaseComponent& operator=(BaseComponent&& other) = delete;
	
		GameObject* m_GameObject{ nullptr };
	
		bool GetEnabled() { return m_Enabled; };
		void SetEnabled(bool enabled) { m_Enabled = enabled; };

	private:
		bool m_Enabled;
	};
}


