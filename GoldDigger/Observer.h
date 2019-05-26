#pragma once

namespace GD
{
	class Entity;

	class Observer
	{
	public:
		virtual ~Observer() {}

		virtual void OnNotify(Entity* caller, unsigned int event) = 0;
	};
}
