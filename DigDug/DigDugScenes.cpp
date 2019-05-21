#include "pch.h"
#include "DigDugScenes.h"
//#include <GameObject.h>
#include <Components.h>

#include "DigDug.h"
#include "DigDugAgents.h"
#include "DigDugCommands.h"
#include "DigDugBehaviours.h"
#include "DigDugStates.h"

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
	GameObject* go_ButtonSinglePlayer = CreateGameObject();
	Texture* onTexture = go_ButtonSinglePlayer->CreateTexture(RenderMode::center);
	Texture* offTexture = go_ButtonSinglePlayer->CreateTexture(RenderMode::center);
	go_ButtonSinglePlayer->AddComponent(new HudText(onTexture, "Single Player", "8bit", { 255, 255, 0 }));
	go_ButtonSinglePlayer->AddComponent(new HudText(offTexture, "Single Player", "8bit"));
	go_ButtonSinglePlayer->AddComponent(new MenuButton(offTexture, onTexture, new StartGame(GameMode::SinglePlayer)));
	go_ButtonSinglePlayer->SetTransform({ {dimensions.x / 2.f, dimensions.y * 0.6f }, { 0.5f, 0.5f }, 0 });

	GameObject* go_ButtonCoop = CreateGameObject();
	onTexture = go_ButtonCoop->CreateTexture(RenderMode::center);
	offTexture = go_ButtonCoop->CreateTexture(RenderMode::center);
	go_ButtonCoop->AddComponent(new HudText(offTexture, "Co-op", "8bit"));
	go_ButtonCoop->AddComponent(new HudText(onTexture, "Co-op", "8bit", { 255, 255, 0 }));
	go_ButtonCoop->AddComponent(new MenuButton(offTexture, onTexture, new StartGame(GameMode::Coop)));
	go_ButtonCoop->SetTransform({ {dimensions.x / 2.f, dimensions.y * 0.67f }, { 0.5f, 0.5f }, 0 });

	GameObject* go_ButtonVersus = CreateGameObject();
	onTexture = go_ButtonVersus->CreateTexture(RenderMode::center);
	offTexture = go_ButtonVersus->CreateTexture(RenderMode::center);
	go_ButtonVersus->AddComponent(new HudText(offTexture, "Versus", "8bit"));
	go_ButtonVersus->AddComponent(new HudText(onTexture, "Versus", "8bit", { 255, 255, 0 }));
	go_ButtonVersus->AddComponent(new MenuButton(offTexture, onTexture, new StartGame(GameMode::Versus)));
	go_ButtonVersus->SetTransform({ {dimensions.x / 2.f, dimensions.y * 0.74f }, { 0.5f, 0.5f }, 0 });

	GameObject* go_ButtonQuit = CreateGameObject();
	onTexture = go_ButtonQuit->CreateTexture(RenderMode::center);
	offTexture = go_ButtonQuit->CreateTexture(RenderMode::center);
	go_ButtonQuit->AddComponent(new HudText(offTexture, "Quit Game", "8bit"));
	go_ButtonQuit->AddComponent(new HudText(onTexture, "Quit Game", "8bit", { 255, 255, 0 }));
	go_ButtonQuit->AddComponent(new MenuButton(offTexture, onTexture, new QuitGame()));
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

	GameObject* go_DigDug = CreateGameObject();
	go_DigDug->AddComponent(new Sprite(go_DigDug->CreateTexture(), "DigDugTemp"));
	PlayerInputAgent* digDugAgent = new PlayerInputAgent(GD::ControllerIndex::Keyboard);
	digDugAgent->AssignAxis(GD::ControllerAxis::LeftStickX, new MoveHorizontal());
	digDugAgent->AssignAxis(GD::ControllerAxis::LeftStickY, new MoveVertical());
	digDugAgent->AssignButton(ControllerButton::A, ButtonState::Pressed, new Attack());
	go_DigDug->AddComponent(new Entity(new DigDugBehaviour(), digDugAgent, new Idle()));
	go_DigDug->AddComponent(new Physics(40.f));
	go_DigDug->AddComponent(new GridSnap(grid));
	go_DigDug->SetPosition(6.f, 0.f, grid);

	if (gameMode == GameMode::Coop) 
	{
		GameObject* go_DigDug2 = CreateGameObject();
		go_DigDug2->AddComponent(new Sprite(go_DigDug2->CreateTexture(), "DigDugTemp"));
		PlayerInputAgent* digDug2Agent = new PlayerInputAgent(GD::ControllerIndex::One);
		digDug2Agent->AssignAxis(GD::ControllerAxis::LeftStickX, new MoveHorizontal());
		digDug2Agent->AssignAxis(GD::ControllerAxis::LeftStickY, new MoveVertical());
		digDug2Agent->AssignButton(ControllerButton::A, ButtonState::Pressed, new Attack());
		go_DigDug2->AddComponent(new Entity(new DigDugBehaviour(), digDug2Agent, new Idle()));
		go_DigDug2->AddComponent(new Physics(40.f));
		go_DigDug2->AddComponent(new GridSnap(grid));
		go_DigDug2->SetPosition(6.f, 1.f, grid);
	}

	GameObject* go_Pooka = CreateGameObject();
	go_Pooka->AddComponent(new Sprite(go_Pooka->CreateTexture(), "PookaTemp"));
	go_Pooka->AddComponent(new Entity(new EnemyBehaviour(), new EnemyBaseAgent(), new Idle()));
	go_Pooka->AddComponent(new Physics(40.f));
	go_Pooka->AddComponent(new GridSnap(grid));
	go_Pooka->SetPosition(5.f, 6.f, grid);

	GameObject* go_Fygar = CreateGameObject();
	go_Fygar->AddComponent(new Sprite(go_Fygar->CreateTexture(), "FygarTemp"));
	if (gameMode == GameMode::Versus) 
	{
		PlayerInputAgent* fygarPlayerAgent = new PlayerInputAgent(ControllerIndex::One);
		fygarPlayerAgent->AssignAxis(ControllerAxis::LeftStickX, new MoveHorizontal());
		fygarPlayerAgent->AssignAxis(ControllerAxis::LeftStickY, new MoveVertical());
		fygarPlayerAgent->AssignButton(ControllerButton::A, ButtonState::Pressed, new Attack());
		go_Fygar->AddComponent(new Entity(new EnemyBehaviour(), fygarPlayerAgent, new Idle()));
	}
	else
		go_Fygar->AddComponent(new Entity(new EnemyBehaviour(), new FygarAgent(), new Idle()));

	go_Fygar->AddComponent(new Physics(40.f));
	go_Fygar->AddComponent(new GridSnap(grid));
	go_Fygar->SetPosition(2.f, 8.f, grid);
}

void DD::Level2Scene::Load() 
{
	
}