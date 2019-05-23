#include "pch.h"
#include "DigDug.h"

#include <string>
#include <SDL.h>
#include <ResourceManager.h>
#include <InputManager.h>
#include <SceneManager.h>
#include <GameObject.h>
#include <structs.h>

#include "DigDugScenes.h"

DD::GameMode DD::DigDug::m_GameMode{ GameMode::SinglePlayer };
const GD::Vector2 DD::DigDug::m_Dimensions{ 224.f, 288.f };
const int DD::DigDug::m_Rows{ 14 };
const int DD::DigDug::m_Cols{ 18 };
const GD::Vector2 DD::DigDug::m_TileDimensions{ DigDug::m_Dimensions.x / float(m_Rows), DigDug::m_Dimensions.y / float(m_Cols) };

const GD::Grid DD::DigDug::m_Grid{ {{0, m_TileDimensions.y * 2.f}, {m_Dimensions.x, m_Dimensions.y - m_TileDimensions.y}}, m_Rows, m_Cols - 3 };

DD::DigDug::DigDug() : GoldDiggerGame(m_Dimensions, 16, 3.f, 0.02f)
{

}

DD::DigDug::~DigDug()
{

}

void DD::DigDug::Initialize() 
{
	LoadResources();

	//Create Scenes
	GD::SceneManager::GetInstance().AddScene(new MenuScene(), static_cast<unsigned int>(Scenes::Menu));
	GD::SceneManager::GetInstance().AddScene(new Level1Scene(), static_cast<unsigned int>(Scenes::Level1));
	GD::SceneManager::GetInstance().AddScene(new Level2Scene(), static_cast<unsigned int>(Scenes::Level2));
	
	GD::KeyboardMap map{};
	map.LeftStickUp = SDL_SCANCODE_W;
	map.LeftStickDown = SDL_SCANCODE_S;
	map.LeftStickRight = SDL_SCANCODE_D;
	map.LeftStickLeft = SDL_SCANCODE_A;
	map.LeftTrigger = SDL_SCANCODE_R;
	map.A = SDL_SCANCODE_SPACE;
	map.RightBumper = SDL_SCANCODE_Y;
	map.LeftStick = SDL_SCANCODE_LALT;
	map.Start = SDL_SCANCODE_RETURN;
	GD::InputManager::GetInstance().MapKeyboard( map );

	GD::SceneManager::GetInstance().LoadScene(static_cast<unsigned int>(Scenes::Menu));
}

void DD::DigDug::LoadResources()
{
	//telling ResourceManager where to find resources
	GD::ResourceManager::GetInstance().Init("Resources/");

	//loading fonts
	GD::ResourceManager::GetInstance().LoadFont("8bit.ttf", 36);

	//loading Sprites
	GD::ResourceManager::GetInstance().LoadTexture("Title.png");
	GD::ResourceManager::GetInstance().LoadTexture("Rock.png");
	GD::ResourceManager::GetInstance().LoadTexture("DigDug.png");
	GD::ResourceManager::GetInstance().LoadTexture("Fygar.png");
	GD::ResourceManager::GetInstance().LoadTexture("Pooka.png");
	GD::ResourceManager::GetInstance().LoadTexture("Background.png");
}