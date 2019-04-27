#pragma once
#include "SceneObject.h"

namespace dae 
{
	class GameObject;

	class BaseComponent : public SceneObject
	{
	public:
		virtual void Update( float deltaTime ) override = 0;
		virtual void Render() const override = 0;

		BaseComponent() = default;
		virtual ~BaseComponent() = default;
		BaseComponent(const BaseComponent& other) = delete;
		BaseComponent(BaseComponent&& other) = delete;
		BaseComponent& operator=(const BaseComponent& other) = delete;
		BaseComponent& operator=(BaseComponent&& other) = delete;
		
		GameObject* gameObject{ nullptr };
	};
}


