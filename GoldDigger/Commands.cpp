#include "GoldDiggerPCH.h"
#include "Commands.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Components.h"
#include "GameObject.h"
#include <thread>

void GD::MoveHorizontal::Execute(const GD::GameObject& /*gameObject*/, float axisValue)
{
	m_Input->movement.x = axisValue;
}

void GD::MoveVertical::Execute(const GD::GameObject& /*gameObject*/, float axisValue)
{
	m_Input->movement.y = -axisValue;
}

void GD::SwitchScene::Execute(const GD::GameObject& /*gameObject*/, float /*axisValue*/)
{
	std::thread clearSceneThread([]{GD::SceneManager::GetInstance().ClearCurrentScene();});
	GD::SceneManager::GetInstance().LoadScene(m_SceneID);
	if (clearSceneThread.joinable())
		clearSceneThread.join();
	GD::SceneManager::GetInstance().SwitchScene(m_SceneID);
}

void GD::CycleButtons::Execute(const GD::GameObject& /*gameObject*/, float axisValue)
{
	if (!GD::MenuButton::s_ActiveButton)
		return;

	if (m_Enabled)
	{
		if (axisValue > 0.7f)
		{
			GD::MenuButton::s_ActiveButton = GD::MenuButton::s_ActiveButton->m_NextButton;
			m_Enabled = false;
		}
		else if (axisValue < -0.7f)
		{
			GD::MenuButton::s_ActiveButton = GD::MenuButton::s_ActiveButton->m_PrevButton;
			m_Enabled = false;
		}
	}
	else
		m_Enabled = abs(axisValue) < 0.5f;
}

void GD::ExecuteCurrentButton::Execute(const GD::GameObject& /*gameObject*/, float /*axisValue*/)
{
	if (GD::MenuButton::s_ActiveButton)
		GD::MenuButton::s_ActiveButton->ExecuteCommand();
}

void GD::QuitGame::Execute(const GD::GameObject& /*gameObject*/, float /*axisValue*/) 
{
	SDL_Event quitEvent{};
	quitEvent.type = SDL_QUIT;
	SDL_PushEvent(&quitEvent);
}