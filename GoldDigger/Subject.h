#pragma once
#include "BaseComponent.h"
#include <vector>

namespace GD 
{
	class Observer;
	class Entity;

	class Subject
	{
	public:
		void AddObserver(Observer* observer);
		void RemoveObserver(Observer* observer);
		void Notify(Entity* caller, unsigned int eventID);

	private:
		std::vector<Observer*> m_Observers;
	};
}


