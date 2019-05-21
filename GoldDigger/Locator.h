#pragma once
#include "Audio.h"

namespace GD 
{
	class Locator
	{
	public:
		static void initialize() { m_Service = &m_NullService; }

		static Audio& getAudio() { return *m_Service; }

		static void provide(Audio* service)
		{
			if (service == NULL)
			{
				// Revert to null service.
				m_Service = &m_NullService;
			}
			else
			{
				m_Service = service;
			}
		}

	private:
		static Audio* m_Service;
		static NullAudio m_NullService;
	};
}
