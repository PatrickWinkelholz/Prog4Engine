#pragma once
#include "BaseComponent.h"
#include "structs.h"

namespace GD
{
	// 
	class EntityBehaviour
	{
	public:
		EntityBehaviour() = default;
		virtual ~EntityBehaviour() = default;

		virtual GD::State* HandleInput() = 0;
	};

	//This component is needed to hold the specific behaviour (pooka, fygar, digdug...)
	//If those were seperate components GetComponent() wouldn't get the interface with the Attack funciton
	class Entity : public BaseComponent
	{
	public:
		Entity(EntityBehaviour* behaviour) : m_Behaviour{ behaviour } {};
		~Entity() = default;

		void Initialize() override {};
		void Update(float elapsedSec) override;
		EntityBehaviour* GetBehaviour() const { return m_Behaviour; };

	private:
		EntityBehaviour* m_Behaviour;
		GD::State* m_State;
	};
}

