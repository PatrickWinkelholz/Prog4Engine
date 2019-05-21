#include "GoldDiggerPCH.h"
#include "Commands.h"
#include "SceneManager.h"
#include "Components.h"
#include "GameObject.h"

void GD::MoveHorizontal::Execute(GD::GameObject& gameObject, float axisValue)
{
	GD::Physics* physics = gameObject.GetComponent<GD::Physics>();
	if (physics)
		physics->SetMoveDirectionX(axisValue);
}

void GD::MoveVertical::Execute(GD::GameObject& gameObject, float axisValue)
{
	GD::Physics* physics = gameObject.GetComponent<GD::Physics>();
	if (physics)
		physics->SetMoveDirectionY(-axisValue);
}

void GD::SwitchScene::Execute(GD::GameObject& /*gameObject*/)
{
	GD::SceneManager::GetInstance().LoadScene(m_SceneID);
	GD::SceneManager::GetInstance().SwitchScene(m_SceneID);
}

void GD::CycleButtons::Execute(GD::GameObject& /*gameObject*/, float axisValue)
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

void GD::ExecuteCurrentButton::Execute(GD::GameObject& /*gameObject*/)
{
	if (GD::MenuButton::s_ActiveButton)
		GD::MenuButton::s_ActiveButton->ExecuteCommand();
	//GD::MenuButton::s_ActiveButton
}

void GD::QuitGame::Execute(GD::GameObject& /*gameObject*/) 
{
	SDL_Event quitEvent{};
	quitEvent.type = SDL_QUIT;
	SDL_PushEvent(&quitEvent);
}