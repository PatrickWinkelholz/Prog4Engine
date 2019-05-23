#include "GoldDiggerPCH.h"
#include "Collider.h"
#include <algorithm>
#include "GameObject.h"
#include "Sprite.h"
#include "Structs.h"

std::vector<GD::Collider*> GD::Collider::m_AllColliders{};

GD::Collider::Collider( Texture* texture, const std::string&& tag)
	: m_CollisionBox{}
	, m_Texture{ texture }
	, m_Tag{ tag }
{
	m_AllColliders.push_back(this);
}

GD::Collider::~Collider()
{
	m_AllColliders.erase(std::remove(m_AllColliders.begin(), m_AllColliders.end(), this));
}

void GD::Collider::Update(float /*elapsedSec*/) 
{
	m_CollisionBox.topLeft = m_GameObject->GetTransform().pos;
	m_CollisionBox.botRight = m_GameObject->GetTransform().pos + (m_Texture->sourceRect.botRight - 
		m_Texture->sourceRect.topLeft) * m_GameObject->GetTransform().scale;
}

GD::GameObject* GD::Collider::CollidesWith( const std::string&& tag ) const 
{
	for (Collider* other : m_AllColliders) 
	{
		if (other->GetTag() != tag)
			continue;

		if (m_CollisionBox.topLeft.x < other->m_CollisionBox.botRight.x &&
			m_CollisionBox.botRight.x > other->m_CollisionBox.topLeft.x &&
			m_CollisionBox.topLeft.y < other->m_CollisionBox.botRight.y &&
			m_CollisionBox.botRight.y > other->m_CollisionBox.topLeft.y)
			return other->m_GameObject;
	}
	return nullptr;
}