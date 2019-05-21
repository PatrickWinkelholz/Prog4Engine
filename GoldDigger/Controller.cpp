#include "GoldDiggerPCH.h"
#include "Controller.h"
#include "Agents.h"

GD::Controller::~Controller()
{
	delete m_Agent;
}

void GD::Controller::Update(float elapsedSec) 
{
	Input input{};
	m_Agent->GenerateInput( *m_GameObject, elapsedSec);
}