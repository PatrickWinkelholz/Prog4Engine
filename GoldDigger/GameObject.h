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

		void SetPosition(float x, float y);
		void SetScale(float x, float y);
		void SetPosition(const Vector2& position);
		void SetScale(const Vector2& scale);
		void SetTransform(const Transform& transform);
		const Transform& GetTransform() const;
		const Vector2& GetPosition() const;
		const Vector2& GetScale() const;

		void AddComponent(BaseComponent* component);

		GameObject();
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	protected:
		std::vector<BaseComponent*> m_Components;
		Transform m_Transform;
	};
}
