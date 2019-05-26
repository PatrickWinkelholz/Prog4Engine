#include "pch.h"
#include "DigDugPrefabs.h"
#include <Scene.h>
#include <Components.h>
#include <Agents.h>
#include <SceneManager.h>

#include "DigDug.h"
#include "DigDugStructs.h"
#include "DigDugAgents.h"
#include "DigDugBehaviours.h"
#include "DigDugStates.h"
#include "DigDugCommands.h"
#include "DigDugObservers.h"

using namespace GD;

GD::GameObject * DD::DigDugPrefabs::CreateMenuButton(GD::Scene& scene, const std::string&& text, 
	const std::string&& font, GD::Command* command,const SDL_Color& onColor, const SDL_Color& offColor)
{
	GameObject* go_Button = scene.CreateGameObject(static_cast<unsigned int>(LayerID::HUD));
	Texture* onTexture = go_Button->CreateTexture(RenderMode::center);
	Texture* offTexture = go_Button->CreateTexture(RenderMode::center);
	go_Button->AddComponent(new HudText(onTexture, std::move(text), std::move(font), onColor));
	go_Button->AddComponent(new HudText(offTexture, std::move(text), std::move(font), offColor));
	go_Button->AddComponent(new MenuButton(offTexture, onTexture, command));
	return go_Button;
}

GD::GameObject * DD::DigDugPrefabs::CreateDigDug(GD::Scene& scene, float x, float y, GD::ControllerIndex index, 
	const GD::Vector2& lifeDisplayPosition, const GD::Grid& grid)
{
	GameObject* go_DigDug = scene.CreateGameObject(static_cast<unsigned int>(LayerID::Foreground));
	Texture* digDugTexture = go_DigDug->CreateTexture();
	Sprite* digDugSprite = new Sprite(digDugTexture, "DigDug");
	digDugSprite->AddAnimation(static_cast<unsigned int>(StateID::Idle), Animation{ 1, 0, { {0, 0}, {16.f, 16.f} } });
	digDugSprite->AddAnimation(static_cast<unsigned int>(StateID::Walking), Animation{ 2, 0.15f, { {0, 0}, {32.f, 16.f} } });
	digDugSprite->AddAnimation(static_cast<unsigned int>(StateID::Digging), Animation{ 2, 0.15f, { {32.f, 0}, {64.f, 16.f} } });
	digDugSprite->AddAnimation(static_cast<unsigned int>(StateID::Dying), Animation{ 5, 0.3f, { {0, 16.f}, {80.f, 32.f} }, false });
	digDugSprite->AddAnimation(static_cast<unsigned int>(StateID::Attacking), Animation{ 1, 0, { {0, 32.f}, {16.f, 48.f} } });
	digDugSprite->AddAnimation(static_cast<unsigned int>(StateID::Pumping), Animation{ 2, 0.2f, { {48.f, 32.f}, {80.f, 48.f} } });
	go_DigDug->AddComponent(new Collider(digDugTexture, "player", 2.0f));
	go_DigDug->AddComponent(digDugSprite);
	PlayerInputAgent* digDugAgent = new PlayerInputAgent( index );
	digDugAgent->AssignAxis(GD::ControllerAxis::LeftStickX, new MoveHorizontal());
	digDugAgent->AssignAxis(GD::ControllerAxis::LeftStickY, new MoveVertical());
	digDugAgent->AssignButton(ControllerButton::X, ButtonState::Pressed, new Attack());
	Entity* digDugEntity = new Entity(new DigDugBehaviour(), digDugAgent, new Idle());
	go_DigDug->AddComponent( digDugEntity );
	go_DigDug->AddComponent(new Physics(40.f));
	go_DigDug->AddComponent(new GridSnap(DigDug::GetGrid()));
	go_DigDug->SetPosition(x, y, grid);

	GameObject* go_LifeDisplay = scene.CreateGameObject(static_cast<unsigned int>(LayerID::HUD));
	Texture* lifeDisplayTexture = go_LifeDisplay->CreateTexture();
	go_LifeDisplay->AddComponent(new Sprite(lifeDisplayTexture, "Lives"));
	go_LifeDisplay->SetPosition(lifeDisplayPosition);

	LifeDisplay* lifeDisplay = new LifeDisplay( lifeDisplayTexture, 3 );
	digDugEntity->AddObserver(lifeDisplay);

	scene.AddObserver(lifeDisplay);

	return go_DigDug;
}

GD::GameObject* DD::DigDugPrefabs::CreatePooka(GD::Scene& scene, float x, float y, 
	DD::ScoreDisplay* scoreDisplay, GD::ControllerIndex index, const GD::Grid& grid)
{
	GameObject* go_Pooka = scene.CreateGameObject(static_cast<unsigned int>(LayerID::Foreground));
	Texture* pookaTexture = go_Pooka->CreateTexture();
	Sprite* pookaSprite = new Sprite(pookaTexture, "Pooka");
	pookaSprite->AddAnimation(static_cast<unsigned int>(StateID::Idle), Animation{ 1, 0, { {0, 0}, {16.f, 16.f} } });
	pookaSprite->AddAnimation(static_cast<unsigned int>(StateID::Walking), Animation{ 2, 0.25f, { {0, 0}, {32.f, 16.f} } });
	pookaSprite->AddAnimation(static_cast<unsigned int>(StateID::Floating), Animation{ 2, 0.25f, { {48.f, 0}, {80.f, 16.f} } });
	pookaSprite->AddAnimation(static_cast<unsigned int>(StateID::Dying), Animation{ 1, 3.f, { {80.f, 0}, {96.f, 16.f} }, false });
	pookaSprite->AddAnimation(static_cast<unsigned int>(StateID::Pumped), Animation{ 4, 0.5f, { {0, 16.f}, {128.f, 48.f} }, false });
	Collider* pookaCollider = new Collider(pookaTexture, "enemy", 2.0f);
	go_Pooka->AddComponent( pookaCollider );
	go_Pooka->AddComponent(pookaSprite);

	Entity* pookaEntity;
	if (index != ControllerIndex::Any)
	{
		PlayerInputAgent* pookaPLayerIDAgent = new PlayerInputAgent(ControllerIndex::One);
		pookaPLayerIDAgent->AssignAxis(ControllerAxis::LeftStickX, new MoveHorizontal());
		pookaPLayerIDAgent->AssignAxis(ControllerAxis::LeftStickY, new MoveVertical());
		pookaPLayerIDAgent->AssignButton(ControllerButton::A, ButtonState::Pressed, new Float());
		pookaEntity = new Entity(new EnemyBehaviour(), pookaPLayerIDAgent, new Idle());
	}
	else
		pookaEntity = new Entity(new EnemyBehaviour(), new EnemyBaseAgent(), new Idle());

	pookaEntity->AddObserver(scoreDisplay);
	go_Pooka->AddComponent(pookaEntity);
	go_Pooka->AddComponent(new Physics(40.f, false, pookaCollider, "tunnel"));
	go_Pooka->AddComponent(new GridSnap(DigDug::GetGrid()));
	go_Pooka->SetPosition(x, y, grid);
	return go_Pooka;
}

GD::GameObject * DD::DigDugPrefabs::CreateFygar(GD::Scene& scene, float x, float y, 
	ScoreDisplay* scoreDisplay, GD::ControllerIndex index, const GD::Grid& grid)
{
	GameObject* go_Fygar = scene.CreateGameObject(static_cast<unsigned int>(LayerID::Foreground));
	Texture* fygarTexture = go_Fygar->CreateTexture();
	Sprite* fygarSprite = new Sprite(fygarTexture, "Fygar");
	fygarSprite->AddAnimation(static_cast<unsigned int>(StateID::Idle), Animation{ 1, 0, { {0, 0}, {16.f, 16.f} } });
	fygarSprite->AddAnimation(static_cast<unsigned int>(StateID::Walking), Animation{ 2, 0.25f, { {0, 0}, {32.f, 16.f} } });
	fygarSprite->AddAnimation(static_cast<unsigned int>(StateID::Floating), Animation{ 2, 0.25f, { {48.f, 0}, {80.f, 16.f} } });
	fygarSprite->AddAnimation(static_cast<unsigned int>(StateID::Dying), Animation{ 1, 3.0f, { {80.f, 0}, {96.f, 16.f} }, false });
	fygarSprite->AddAnimation(static_cast<unsigned int>(StateID::Attacking), Animation{ 1, 0, { {32.f, 0}, {48.f, 16.f} } });
	fygarSprite->AddAnimation(static_cast<unsigned int>(StateID::Charging), Animation{ 2, 0.09f, { {16.f, 0}, {48.f, 16.f} } });
	fygarSprite->AddAnimation(static_cast<unsigned int>(StateID::Pumped), Animation{ 4, 0.65f, { {0, 16.f}, {128.f, 48.f} }, false });
	Collider* fygarCollider = new Collider(fygarTexture, "enemy", 2.0f);
	go_Fygar->AddComponent(fygarCollider);
	go_Fygar->AddComponent(fygarSprite);

	Entity* fygarEntity;
	if (index != ControllerIndex::Any)
	{
		PlayerInputAgent* fygarPLayerIDAgent = new PlayerInputAgent(ControllerIndex::One);
		fygarPLayerIDAgent->AssignAxis(ControllerAxis::LeftStickX, new MoveHorizontal());
		fygarPLayerIDAgent->AssignAxis(ControllerAxis::LeftStickY, new MoveVertical());
		fygarPLayerIDAgent->AssignButton(ControllerButton::A, ButtonState::Pressed, new Float());
		fygarPLayerIDAgent->AssignButton(ControllerButton::X, ButtonState::Pressed, new Attack());
		fygarEntity = new Entity(new EnemyBehaviour(), fygarPLayerIDAgent, new Idle());
	}
	else
		fygarEntity = new Entity(new EnemyBehaviour(), new FygarAgent(), new Idle());

	fygarEntity->AddObserver(scoreDisplay);
	go_Fygar->AddComponent(fygarEntity);
	go_Fygar->AddComponent(new Physics(40.f, false, fygarCollider, "tunnel"));
	go_Fygar->AddComponent(new GridSnap(DigDug::GetGrid()));
	go_Fygar->SetPosition(x, y, grid);
	return go_Fygar;
}

GD::GameObject* DD::DigDugPrefabs::CreateTunnel(GD::Scene& scene) 
{
	GameObject* go_Tunnel = scene.CreateGameObject(static_cast<unsigned int>(LayerID::Tunnel));
	Texture* tunnelTexture = go_Tunnel->CreateTexture();
	go_Tunnel->AddComponent(new Sprite(tunnelTexture, "Tunnel"));
	go_Tunnel->AddComponent(new Collider(tunnelTexture, "tunnel"));
	return go_Tunnel;
}

GD::GameObject* DD::DigDugPrefabs::CreateRock(GD::Scene& scene, float x, float y, const GD::Grid& grid) 
{
	GameObject* go_Rock = scene.CreateGameObject(static_cast<unsigned int>(LayerID::Foreground));
	Texture* rockTexture = go_Rock->CreateTexture();
	Sprite* rockSprite = new Sprite(rockTexture, "Rock");
	rockSprite->AddAnimation(static_cast<unsigned int>(StateID::Idle), Animation{ 1, 0, { {16.f, 0}, {32.f, 16.f} } });
	rockSprite->AddAnimation(static_cast<unsigned int>(StateID::Charging), Animation{ 2, 0.2f, { {0, 0}, {32.f, 16.f} } });
	rockSprite->AddAnimation(static_cast<unsigned int>(StateID::Walking), Animation{ 1, 0, { {16.f, 0}, {32.f, 16.f} } });
	rockSprite->AddAnimation(static_cast<unsigned int>(StateID::Dying), Animation{ 3, 0.4f, { {16.f, 0}, {64.f, 16.f} }, false });
	go_Rock->AddComponent( rockSprite );
	Collider* rockCollider = new Collider(rockTexture, "", 2.f);
	go_Rock->AddComponent( rockCollider );
	go_Rock->AddComponent(new Physics(40.f, true, rockCollider, "tunnel"));
	go_Rock->AddComponent(new Entity(new RockBehaviour(), nullptr, new Idle()));
	
	GameObject* go_RockTunnel = DD::DigDugPrefabs::CreateTunnel( scene );
	go_RockTunnel->SetPosition(x, y, grid);
	go_Rock->SetPosition(go_RockTunnel->GetPosition().x, go_RockTunnel->GetPosition().y + 2.0f);
	return go_Rock;
}

void DD::DigDugPrefabs::GenerateTunnels(GD::Scene& scene, const GD::Vector2& start, const GD::Vector2& direction, int length, const GD::Grid& grid) 
{
	Vector2 startPos{ start };
	if (grid.cols > 0 && grid.rows > 0)
		startPos = grid.bounds.topLeft + grid.GetTileDimensions() * start;

	for (int i{}; i < length; i++) 
	{
		GameObject* go_Tunnel = CreateTunnel(scene);
		go_Tunnel->SetPosition(startPos + direction.Normalized() * 4.0f * float(i));
	}
}