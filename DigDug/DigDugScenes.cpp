#include "pch.h"
#include "DigDugScenes.h"
//#include <GameObject.h>
#include <Components.h>
#include <Structs.h>

#include "DigDug.h"
#include "DigDugAgents.h"
#include "DigDugCommands.h"
#include "DigDugBehaviours.h"
#include "DigDugStates.h"
#include "DigDugPrefabs.h"

using namespace GD;

void DD::MenuScene::Load() 
{
	Vector2 dimensions{ DigDug::GetDimensions() };

	//logo
	GameObject* go_Logo = CreateGameObject();
	go_Logo->AddComponent(new Sprite(go_Logo->CreateTexture(RenderMode::center), "Title"));
	go_Logo->SetPosition(dimensions.x / 2.f, dimensions.y * 0.35f);

	//'welcome to' headline
	GameObject* go_Headline = CreateGameObject();
	go_Headline->AddComponent(new HudText(go_Headline->CreateTexture(RenderMode::center), "Welcome to", "8bit"));
	go_Headline->SetPosition(dimensions.x / 2.f, dimensions.y * 0.25f);
	go_Headline->SetScale(0.5f, 0.5f);

	//player controller
	GameObject* go_PlayerController = CreateGameObject();
	PlayerInputAgent* playerInput = new PlayerInputAgent(ControllerIndex::Any);
	playerInput->AssignButton(GD::ControllerButton::A, GD::ButtonState::Pressed, new ExecuteCurrentButton());
	playerInput->AssignAxis(GD::ControllerAxis::LeftStickY, new CycleButtons());
	go_PlayerController->AddComponent(new Controller(playerInput));

	//buttons
	GameObject* go_ButtonSinglePlayer = DigDugPrefabs::CreateMenuButton(*this, "Single Player", "8bit", new StartGame(GameMode::SinglePlayer));
	go_ButtonSinglePlayer->SetTransform({ {dimensions.x / 2.f, dimensions.y * 0.6f }, { 0.5f, 0.5f }, 0 });

	GameObject* go_ButtonCoop = DigDugPrefabs::CreateMenuButton(*this, "Co-op", "8bit", new StartGame(GameMode::Coop));
	go_ButtonCoop->SetTransform({ {dimensions.x / 2.f, dimensions.y * 0.67f }, { 0.5f, 0.5f }, 0 });

	GameObject* go_ButtonVersus = DigDugPrefabs::CreateMenuButton(*this, "Versus", "8bit", new StartGame(GameMode::Versus));
	go_ButtonVersus->SetTransform({ {dimensions.x / 2.f, dimensions.y * 0.74f }, { 0.5f, 0.5f }, 0 });

	GameObject* go_ButtonQuit = DigDugPrefabs::CreateMenuButton(*this, "Quit Game", "8bit", new QuitGame());
	go_ButtonQuit->SetTransform({ {dimensions.x / 2.f, dimensions.y * 0.81f }, { 0.5f, 0.5f }, 0 });
}

void DD::Level1Scene::Load() 
{
	Grid grid{ DigDug::GetGrid() };
	GameMode gameMode{ DigDug::GetGameMode() };

	GameObject* go_Background = CreateGameObject();
	go_Background->AddComponent(new Sprite(go_Background->CreateTexture(), "Background"));

	GameObject* go_FPSCounter = CreateGameObject();
	HudText* fpsHudText = new HudText(go_FPSCounter->CreateTexture(), "FPS", "8bit", SDL_Color{ 255, 255, 0 });
	go_FPSCounter->AddComponent(fpsHudText);
	go_FPSCounter->AddComponent(new FPSCounter(fpsHudText));
	go_FPSCounter->SetScale(1.f / 3.f, 1.f / 3.f);

	GameObject* go_DigDug = DD::DigDugPrefabs::CreateDigDug( *this, GD::ControllerIndex::Keyboard );
	go_DigDug->SetPosition(6.f, 0.f, grid);

	if (gameMode == GameMode::Coop) 
	{
		GameObject* go_DigDug2 = DD::DigDugPrefabs::CreateDigDug(*this, GD::ControllerIndex::One);
		go_DigDug2->SetPosition(6.f, 1.f, grid);
	}
	
	GameObject* go_Pooka = DD::DigDugPrefabs::CreatePooka(*this);
	go_Pooka->SetPosition(5.f, 6.f, grid);

	GameObject* go_Fygar = DD::DigDugPrefabs::CreateFygar(*this,
		gameMode == GameMode::Versus ? GD::ControllerIndex::One : GD::ControllerIndex::Any);
	go_Fygar->SetPosition(2.f, 8.f, grid);
}

void DD::Level2Scene::Load() 
{
	
}