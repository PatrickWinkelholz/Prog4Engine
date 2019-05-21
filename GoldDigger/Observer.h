#pragma once
#include "GameObject.h"

namespace GD
{
	class Observer
	{
	public:
		virtual ~Observer() {}
		virtual void onNotify(GameObject& caller, Event event) = 0;
	};
}
