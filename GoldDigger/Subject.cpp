#include "GoldDiggerPCH.h"
#include "Subject.h"
#include "Observer.h"

void GD::Subject::AddObserver(Observer* observer)
{
	m_Observers.push_back(observer);
}

void GD::Subject::RemoveObserver(Observer* observer)
{
	m_Observers.erase(std::find(m_Observers.begin(), m_Observers.end(), observer));
}

void GD::Subject::Notify(Entity* caller, unsigned int eventID)
{
	for (Observer* observer : m_Observers)
		observer->OnNotify(caller, eventID);
}