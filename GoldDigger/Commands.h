#pragma once
#include <string>

namespace GD 
{
	struct Input;
	class GameObject;

	//TODO: merge these 2 in one
	class Command
	{
		friend class Agent;
	public:
		Command() = default;
		virtual ~Command() = default;

		virtual void Execute(const GameObject& gameObject, float axisValue = 0) = 0;

	protected:
		Input* m_Input;
	};

	class MoveHorizontal : public Command
	{
	public:
		~MoveHorizontal() = default;
		void Execute(const GameObject& gameObject, float axisValue = 0) override;
	};

	class MoveVertical : public Command
	{
	public:
		~MoveVertical() = default;
		void Execute(const GameObject& gameObject, float axisValue = 0) override;
	};

	class SwitchScene : public Command
	{
	public:
		SwitchScene(unsigned int id) : m_SceneID{ id } {};
		~SwitchScene() = default;
		void Execute(const GameObject& gameObject, float axisValue = 0) override;

	private:
		unsigned int m_SceneID;
	};

	class CycleButtons : public Command
	{
	public:
		~CycleButtons() = default;
		void Execute(const GameObject& gameObject, float axisValue = 0) override;

	private:
		bool m_Enabled = true;
	};

	class ExecuteCurrentButton : public Command
	{
	public:
		~ExecuteCurrentButton() = default;
		void Execute(const GameObject& gameObject, float axisValue = 0) override;
	};

	class QuitGame : public Command 
	{
	public:
		~QuitGame() = default;
		void Execute(const GameObject& gameObject, float axisValue = 0) override;
	};
}



