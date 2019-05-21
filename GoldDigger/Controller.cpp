#include "GoldDiggerPCH.h"
#include "Controller.h"
#include "Agents.h"
#include "Structs.h"

GD::Controller::~Controller()
{
	delete m_Agent;
}

void GD::Controller::Update( float deltaTime ) 
{
	m_Agent->HandleInput( *m_GameObject );
}
