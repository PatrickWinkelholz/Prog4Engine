#pragma once
#include "BaseComponent.h"
#include "structs.h"

namespace GD 
{
	class Physics : public BaseComponent
	{
	public:
		//TODO: maybe add acceleration / deceleration
		//Physics(float acceleration, float maxSpeed, float deceleration, bool useGravity)
		Physics(float maxSpeed, bool useGravity = false)
			: m_MaxSpeed{ maxSpeed }
			, m_UseGravity{ useGravity }
			, m_Velocity{ 0, 0 }
			, m_Acceleration{0, 0}
			{};
		~Physics() = default;

		void Initialize() override;
		void Update(float deltaTime) override;

		void SetMoveDirection(const Vector2& direction) { m_MoveDirection = direction; };
		void SetMoveDirectionX(float x) { m_MoveDirection.x = x; };
		void SetMoveDirectionY(float y) { m_MoveDirection.y = y; };

	private:
		float m_MaxSpeed;
		bool m_UseGravity;
		Vector2 m_Acceleration;
		Vector2 m_Velocity;
		Vector2 m_MoveDirection;
		static const Vector2 m_Gravity;
	};
}


