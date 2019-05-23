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
		Collider( Texture* texture, const std::string&& tag = "default" );
		~Collider();

		void Initialize() override {};
		void Update(float elapsedSec) override;

		std::string GetTag() const { return m_Tag; };
		GameObject* CollidesWith( const std::string&& tag ) const;

	private:
		std::string m_Tag;
		Texture* m_Texture;
		Rect m_CollisionBox;
		static std::vector<Collider*> m_AllColliders;
	};
}
