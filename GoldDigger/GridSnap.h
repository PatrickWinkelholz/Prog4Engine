#pragma once
#include "BaseComponent.h"
#include "Structs.h"

namespace GD 
{
	class GridSnap : public BaseComponent
	{
	public:
		GridSnap(const Grid& grid) : m_Grid(grid) {};
		~GridSnap() = default;

		void Initialize() override;
		void Update(float deltaTime) override;

	private:
		float Clamp(float n, float min, float max) const;

		const Grid m_Grid;
	};
}


