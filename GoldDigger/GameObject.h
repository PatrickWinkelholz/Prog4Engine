#pragma once
#include <memory>
#include <vector>
#include "Structs.h"

namespace GD
{
	class BaseComponent;

	class GameObject final
	{
	public:
		void Initialize();
		void Update( float deltaTime );
		void Render() const;

		void SetPosition(float x, float y, const Grid& grid = {});
		void SetPosition(const Vector2& position, const Grid& grid = {}) { SetPosition(position.x, position.y, grid); };
		void SetPositionX(float x, const Grid& grid = {}) { SetPosition(x, m_Transform.pos.y, grid); };
		void SetPositionY(float y, const Grid& grid = {}) { SetPosition(m_Transform.pos.x, y, grid); };

		void SetScale(const Vector2& scale) { m_Transform.scale = scale; };
		void SetScale(float x, float y) { m_Transform.scale = { x, y }; };
		void SetScaleX(float x) { m_Transform.scale.x = x; };
		void SetScaleY(float y) { m_Transform.scale.y = y; };

		void SetTransform(const Transform& transform) { m_Transform = transform; };

		const Transform& GetTransform() const { return m_Transform; };
		const Vector2& GetPosition() const { return m_Transform.pos; };
		const Vector2& GetScale() const { return m_Transform.scale; };

		void AddComponent(BaseComponent* component);
		template <class T>
		T* GetComponent() const 
		{
			for (unsigned int i{}; i < m_Components.size(); i++)
			{
				if (typeid(*m_Components[i]) == typeid(T))
					return dynamic_cast<T*>(m_Components[i]);
			}
			return nullptr;
		};

		Texture* CreateTexture(RenderMode mode = RenderMode::corner, bool enabled = true);

		GameObject();
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	protected:
		std::vector<Texture*> m_Textures;
		std::vector<BaseComponent*> m_Components;
		Transform m_Transform;
	};
}
