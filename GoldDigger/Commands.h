#pragma once
#include <string>

namespace GD 
{
	class GameObject;

	class Command
	{
	public:
		Command() = default;
		virtual ~Command() = default;

		virtual void Execute(GameObject& gameObject) = 0;
	};

	class AxisCommand
	{
	public:
		AxisCommand() = default;
		virtual ~AxisCommand() = default;

		virtual void Execute(GameObject& gameObject, float axisValue) = 0;
	};

	class MoveHorizontal : public GD::AxisCommand
	{
	public:
		~MoveHorizontal() = default;
		void Execute(GD::GameObject& gameObject, float axisValue) override;
	};

	class MoveVertical : public GD::AxisCommand
	{
	public:
		~MoveVertical() = default;
		void Execute(GD::GameObject& gameObject, float axisValue) override;
	};

	class SwitchScene : public GD::Command
	{
	public:
		SwitchScene(unsigned int id) : m_SceneID{ id } {};
		~SwitchScene() = default;
		void Execute(GD::GameObject& gameObject) override;

	private:
		unsigned int m_SceneID;
	};

	class CycleButtons : public GD::AxisCommand
	{
	public:
		~CycleButtons() = default;
		void Execute(GD::GameObject& gameObject, float axisValue) override;

	private:
		bool m_Enabled = true;
	};

	class ExecuteCurrentButton : public GD::Command
	{
	public:
		~ExecuteCurrentButton() = default;
		void Execute(GD::GameObject& gameObject) override;
	};

	class QuitGame : public GD::Command 
	{
	public:
		~QuitGame() = default;
		void Execute(GD::GameObject& gameObject) override;
	};
}



