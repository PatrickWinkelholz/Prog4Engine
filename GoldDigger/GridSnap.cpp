#include "GoldDiggerPCH.h"
#include "GridSnap.h"
#include  "structs.h"
#include "GameObject.h"
#include <iostream>
#include <algorithm>

void GD::GridSnap::Initialize()
{
	
}

void GD::GridSnap::Update(float deltaTime) 
{
	Vector2 pos = m_GameObject->GetPosition();
	float nearestRow{ Clamp(std::round(pos.x / m_Grid.tileDimensions.x) * m_Grid.tileDimensions.x, m_Grid.bounds.topLeft.x, m_Grid.bounds.botRight.x) };
	float nearestCol{ Clamp(std::round(pos.y / m_Grid.tileDimensions.y) * m_Grid.tileDimensions.y, m_Grid.bounds.topLeft.y, m_Grid.bounds.botRight.y) };
	
	//Debug printing
	//std::cout << "(" << nearestRow << "|" << nearestCol << ")\n";

	if (abs(pos.x - nearestRow) < abs(pos.y - nearestCol))
		m_GameObject->SetPosition({ nearestRow, Clamp(pos.y, m_Grid.bounds.topLeft.y, m_Grid.bounds.botRight.y - m_Grid.tileDimensions.y) });
	else
		m_GameObject->SetPosition({ Clamp(pos.x, m_Grid.bounds.topLeft.x, m_Grid.bounds.botRight.x - m_Grid.tileDimensions.x), nearestCol });
}

float GD::GridSnap::Clamp(float n, float min, float max) const
{
	return std::max(min, std::min(n, max));
}
