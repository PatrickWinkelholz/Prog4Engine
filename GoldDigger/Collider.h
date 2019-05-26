#pragma once
#include "BaseComponent.h"
#include "Structs.h"
#include <vector>

namespace GD 
{
	struct Texture;

	class Collider : public GD::BaseComponent
	{
	public:
		Collider( Texture* texture, const std::string&& tag = "default", float buffer = 0);
		~Collider(  );

		void Initialize() override {};
		void Update(float elapsedSec) override;

		std::string GetTag() const { return m_Tag; };
		void SetTag( std::string&& tag) { m_Tag = tag; }
		GameObject* CollidesWith( const std::string&& tag ) const;
		bool IsInside(const std::string&& tag) const;
		void UpdateCollisionBox();
		static GameObject* FindNearest( const Vector2& pos, const std::string&& tag );

	private:
		std::string m_Tag;
		float m_Buffer;
		Texture* m_Texture;
		Rect m_CollisionBox;
		static std::vector<Collider*> m_AllColliders;
	};
}
