#include "GoldDiggerPCH.h"
#include "MenuButton.h"
#include "structs.h"
#include "Commands.h"
#include "GameObject.h"

GD::MenuButton* GD::MenuButton::s_ActiveButton{ nullptr };

GD::MenuButton::MenuButton( GD::Texture* off, GD::Texture* on, Command* command, float activeScaleFactor ) 
	: m_OffTexture{ off }
	, m_OnTexture{ on }
	, m_Focused{ false }
	, m_Command{ command }
	, m_ActiveScaleFactor{ activeScaleFactor }
	, m_NextButton{ this }
	, m_PrevButton{ this }
{
	
}

void GD::MenuButton::ExecuteCommand() 
{
	Input input{};
	if (m_Command)
		m_Command->Execute( *m_GameObject );
}

void GD::MenuButton::Initialize() 
{
	m_OriginalScale = m_GameObject->GetScale();
	m_OnTexture->enabled = false;
	if (!s_ActiveButton)
	{
		s_ActiveButton = this;
		GainFocus();
	}
	else
	{
		m_NextButton = s_ActiveButton->m_NextButton;
		m_PrevButton = s_ActiveButton;
		m_NextButton->m_PrevButton = this;
		s_ActiveButton->m_NextButton = this;
	}
}

void GD::MenuButton::Update(float/* deltaTime*/) 
{
	if (s_ActiveButton == this && !m_Focused)
		GainFocus();
	else if (s_ActiveButton != this && m_Focused)
		LooseFocus();
}

void GD::MenuButton::GainFocus() 
{
	m_Focused = true;
	m_OffTexture->enabled = false;
	m_OnTexture->enabled = true;
	m_GameObject->SetScale(m_OriginalScale * m_ActiveScaleFactor);
}

void GD::MenuButton::LooseFocus() 
{
	m_Focused = false;
	m_OnTexture->enabled = false;
	m_OffTexture->enabled = true;
	m_GameObject->SetScale( m_OriginalScale );
}