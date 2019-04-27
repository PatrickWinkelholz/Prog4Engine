#pragma once
#include <memory>
#include "SceneObject.h"

namespace dae
{
	class BaseComponent;

	struct Transform 
	{
		float x;
		float y;
		float z;
	};

	class GameObject final : public SceneObject
	{
	public:
		void Update( float deltaTime ) override;
		void Render() const override;

		//void SetTexture(const std::string& filename);
		void SetPosition(float x, float y);
		const Transform& GetPosition() const;
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
		//std::shared_ptr<Texture2D> mTexture;
	};
}
