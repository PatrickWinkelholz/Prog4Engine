#pragma once

namespace GD 
{
	class GameObject;

	class Command
	{
	public:
		Command() = default;
		virtual ~Command() = default;

		virtual void Execute( GameObject& gameObject ) = 0;
		void SetData(float* data) { m_InputData = data; };

	protected:
		//TODO: change this to void* or find a better solution
		float* m_InputData;
	};
}



