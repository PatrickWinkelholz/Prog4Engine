#include "GoldDiggerPCH.h"
#include "Collider.h"
#include <algorithm>
#include "GameObject.h"
#include "Sprite.h"
#include "Structs.h"

std::vector<GD::Collider*> GD::Collider::m_AllColliders{};

GD::Collider::Collider( Texture* texture, const std::string&& tag, float buffer)
	: m_CollisionBox{}
	, m_Texture{ texture }
	, m_Tag{ tag }
	, m_Buffer{ buffer }
{
	m_AllColliders.push_back(this);
}

GD::Collider::~Collider()
{
	m_AllColliders.erase(std::remove(m_AllColliders.begin(), m_AllColliders.end(), this));
}

void GD::Collider::Update(float /*elapsedSec*/) 
{
	UpdateCollisionBox();
}

void GD::Collider::UpdateCollisionBox() 
{
	m_CollisionBox.topLeft = m_GameObject->GetTransform().pos + m_Buffer;
	m_CollisionBox.botRight = m_GameObject->GetTransform().pos + (m_Texture->sourceRect.botRight -
		m_Texture->sourceRect.topLeft) * m_GameObject->GetTransform().scale - m_Buffer;
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
		{
			if (this != other)
				return other->m_GameObject;
		}
	}
	return nullptr;
}

bool GD::Collider::IsInside(const std::string&& tag) const 
{
	//starting with the initial collisionbox substract from it's area every time a collider partly overlaps with it.
	//if in the end the outside area that is left has a width and a height of 0 the collisionbox is fully covered
	//(this will only work if all other colliders are the same size or bigger than m_Collisionbox)
	//(also this won't work for objects not fully on the grid)
	GD::Rect outside = m_CollisionBox;

	for (Collider* other : m_AllColliders) 
	{
		if (other->GetTag() != tag)
			continue;

		//beativul
		if (outside.topLeft.y >= other->m_CollisionBox.topLeft.y &&
			outside.botRight.y <= other->m_CollisionBox.botRight.y) 
		{
			if (outside.topLeft.x < other->m_CollisionBox.topLeft.x &&
				outside.botRight.x > other->m_CollisionBox.topLeft.x)
			{
				outside.botRight.x = other->m_CollisionBox.topLeft.x;
			}
			else if (outside.botRight.x > other->m_CollisionBox.botRight.x &&
				outside.topLeft.x < other->m_CollisionBox.botRight.x)
			{
				outside.topLeft.x = other->m_CollisionBox.botRight.x;
			}
			else if (outside.topLeft.x >= other->m_CollisionBox.topLeft.x &&
				outside.botRight.x <= other->m_CollisionBox.botRight.x)
				return true;
		}
		else if (outside.topLeft.x >= other->m_CollisionBox.topLeft.x &&
			outside.botRight.x <= other->m_CollisionBox.botRight.x)
		{
			if (outside.topLeft.y < other->m_CollisionBox.topLeft.y &&
				outside.botRight.y > other->m_CollisionBox.topLeft.y)
			{
				outside.botRight.y = other->m_CollisionBox.topLeft.y;
			}
			else if (outside.botRight.y > other->m_CollisionBox.botRight.y &&
				outside.topLeft.y < other->m_CollisionBox.botRight.y)
			{
				outside.topLeft.y = other->m_CollisionBox.botRight.y;
			}
			else if (outside.topLeft.y >= other->m_CollisionBox.topLeft.y &&
				outside.botRight.y <= other->m_CollisionBox.botRight.y)
				return true;
		}
		else continue;

		if (abs(outside.GetWidth()) < 0.01f && abs(outside.GetHeight()) < 0.01f)
			return true;
	}
	return false;
}

GD::GameObject* GD::Collider::FindNearest(const Vector2& pos, const std::string&& tag)
{
	GameObject* nearest = nullptr;
	for (Collider* other : m_AllColliders)
	{
		if (other->GetTag() != tag)
			continue;

		if (!nearest)
			nearest = other->m_GameObject;

		else if ((pos - nearest->GetPosition()).LengthSquared() > (pos - other->m_GameObject->GetPosition()).LengthSquared())
			nearest = other->m_GameObject;
	}
	return nearest;
}