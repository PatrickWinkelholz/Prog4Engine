#include "pch.h"
#include <memory>
#include <string>
#include <SDL.h>
#include "DigDug.h"

#include "Components.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "GameObject.h"
#include "InputManager.h"
#include "structs.h"
#include "Controllers.h"
#include "Commands.h"

using namespace GD;

DigDug::DigDug() : GoldDiggerGame({ 240.f, 240.f }, 16, 3.f, 0.02f, 16.f)
{

}

DigDug::~DigDug()
{

}

void DigDug::Initialize() 
{
	LoadResources();
	LoadScenes();

	KeyboardMap map{};
	map.LeftStickUp = SDL_SCANCODE_W;
	map.LeftStickDown = SDL_SCANCODE_S;
	map.LeftStickRight = SDL_SCANCODE_D;
	map.LeftStickLeft = SDL_SCANCODE_A;
	map.LeftTrigger = SDL_SCANCODE_R;
	map.A = SDL_SCANCODE_SPACE;
	map.RightBumper = SDL_SCANCODE_Y;
	map.LeftStick = SDL_SCANCODE_LALT;
	InputManager::GetInstance().MapKeyboard( map );
}

void DigDug::LoadScenes() 
{
	Scene& menuScene = SceneManager::GetInstance().CreateScene("menu");
	//Scene& level1Scene = SceneManager::GetInstance().CreateScene("level1");
	SceneManager::GetInstance().SetActiveScene(menuScene);

	/*std::shared_ptr<GameObject> go_Background = std::make_shared<GameObject>();
	go_Background->AddComponent(new Texture("background"));
	menuScene.Add(go_Background);*/

	std::shared_ptr<GameObject> go_Logo = std::make_shared<GameObject>();
	go_Logo->AddComponent(new Texture("Title", RenderMode::center));
	go_Logo->SetPosition(m_Dimensions.x / 2.f, m_Dimensions.y / 2.f);
	menuScene.Add(go_Logo);

	std::shared_ptr<GameObject> go_Headline = std::make_shared<GameObject>();
	go_Headline->AddComponent(new HudText("Welcome to", "8bit", RenderMode::center, SDL_Color{255, 255, 255}));
	go_Headline->SetPosition(m_Dimensions.x / 2.f, m_Dimensions.y * 0.4f);
	go_Headline->SetScale(0.5f, 0.5f);
	menuScene.Add(go_Headline);

	std::shared_ptr<GameObject> go_FPSCounter = std::make_shared<GameObject>();
	go_FPSCounter->AddComponent(new FPSCounter( "8bit" ));
	go_FPSCounter->SetScale(1.f / 3.f, 1.f / 3.f);
	menuScene.Add(go_FPSCounter);

	std::shared_ptr<GameObject> go_DigDug = std::make_shared<GameObject>();
	go_DigDug->AddComponent(new Texture("Rock", RenderMode::center));
	go_DigDug->SetPosition(m_Dimensions.x / 2.f, m_Dimensions.y / 2.f);
	PlayerController* controller = new PlayerController( GD::ControllerIndex::One );
	controller->AssignAxis(GD::ControllerAxis::LeftStickX, new MoveHorizontal());
	controller->AssignAxis(GD::ControllerAxis::LeftStickY, new MoveVertical());
	go_DigDug->AddComponent( controller );
	menuScene.Add(go_DigDug);
}

void DigDug::LoadResources()
{
	//telling
	ResourceManager::GetInstance().Init("Resources/");

	//loading fonts
	ResourceManager::GetInstance().LoadFont("8bit.ttf", 36);

	//loading textures
	ResourceManager::GetInstance().LoadTexture("Title.png");
	ResourceManager::GetInstance().LoadTexture("Rock.png");
	//ResourceManager::GetInstance().LoadTexture("background.jpg");
}