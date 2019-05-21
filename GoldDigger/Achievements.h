#pragma once
#include "Observer.h"
#include <map>
#include <string>
#include "GameObject.h"
#include "structs.h"

namespace GD 
{
	class Achievements : public Observer
	{
	public:

		Achievements() = default;

		virtual void onNotify(GameObject& caller, Event event)
		{
			for (auto& pair : m_Achievements) 
			{
				if (pair.first == event) 
				{
					pair.second.counter++;
					if (pair.second.counter == pair.second.requirement)
						Unlock(pair.second);
				}
			}
		}

		void AddAchievement( Event event, const Achievement& achievement ) 
		{
			m_Achievements.insert( std::pair<Event, Achievement>(event, achievement) );
		}

	private:

		void Unlock(Achievement& achievement)
		{
			if (achievement.locked)
			{
				//SceneManager::
				achievement.locked = false;
			}
		}

		std::multimap<Event, Achievement> m_Achievements;
	};
}
