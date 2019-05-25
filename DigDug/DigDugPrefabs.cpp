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

using namespace GD;

GD::GameObject * DD::DigDugPrefabs::CreateMenuButton(GD::Scene& scene, const std::string&& text, 
	const std::string&& font, GD::Command* command,const SDL_Color& onColor, const SDL_Color& offColor)
{
	GameObject* go_Button = scene.CreateGameObject(static_cast<unsigned int>(Layer::HUD));
	Texture* onTexture = go_Button->CreateTexture(RenderMode::center);
	Texture* offTexture = go_Button->CreateTexture(RenderMode::center);
	go_Button->AddComponent(new HudText(onTexture, std::move(text), std::move(font), onColor));
	go_Button->AddComponent(new HudText(offTexture, std::move(text), std::move(font), offColor));
	go_Button->AddComponent(new MenuButton(offTexture, onTexture, command));
	return go_Button;
}

GD::GameObject * DD::DigDugPrefabs::CreateDigDug(GD::Scene& scene, GD::ControllerIndex index )
{
	GameObject* go_DigDug = scene.CreateGameObject(static_cast<unsigned int>(Layer::Foreground));
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
	go_DigDug->AddComponent(new Entity(new DigDugBehaviour(), digDugAgent, new Idle()));
	go_DigDug->AddComponent(new Physics(40.f));
	go_DigDug->AddComponent(new GridSnap(DigDug::GetGrid()));
	return go_DigDug;
}

GD::GameObject* DD::DigDugPrefabs::CreatePooka(GD::Scene& scene, GD::ControllerIndex index)
{
	GameObject* go_Pooka = scene.CreateGameObject(static_cast<unsigned int>(Layer::Foreground));
	Texture* pookaTexture = go_Pooka->CreateTexture();
	Sprite* pookaSprite = new Sprite(pookaTexture, "Pooka");
	pookaSprite->AddAnimation(static_cast<unsigned int>(StateID::Idle), Animation{ 1, 0, { {0, 0}, {16.f, 16.f} } });
	pookaSprite->AddAnimation(static_cast<unsigned int>(StateID::Walking), Animation{ 2, 0.25f, { {0, 0}, {32.f, 16.f} } });
	pookaSprite->AddAnimation(static_cast<unsigned int>(StateID::Floating), Animation{ 2, 0.25f, { {48.f, 0}, {80.f, 16.f} } });
	pookaSprite->AddAnimation(static_cast<unsigned int>(StateID::Dying), Animation{ 1, 0, { {80.f, 0}, {96.f, 16.f} } });
	pookaSprite->AddAnimation(static_cast<unsigned int>(StateID::Pumped), Animation{ 4, 0.5f, { {0, 16.f}, {128.f, 48.f} } });
	Collider* pookaCollider = new Collider(pookaTexture, "enemy", 2.0f);
	go_Pooka->AddComponent( pookaCollider );
	go_Pooka->AddComponent(pookaSprite);

	if (index != ControllerIndex::Any)
	{
		PlayerInputAgent* pookaPlayerAgent = new PlayerInputAgent(ControllerIndex::One);
		pookaPlayerAgent->AssignAxis(ControllerAxis::LeftStickX, new MoveHorizontal());
		pookaPlayerAgent->AssignAxis(ControllerAxis::LeftStickY, new MoveVertical());
		pookaPlayerAgent->AssignButton(ControllerButton::A, ButtonState::Pressed, new Float());
		go_Pooka->AddComponent(new Entity(new EnemyBehaviour(), pookaPlayerAgent, new Idle()));
	}
	else
		go_Pooka->AddComponent(new Entity(new EnemyBehaviour(), new EnemyBaseAgent(), new Idle()));

	go_Pooka->AddComponent(new Physics(40.f, false, pookaCollider, "tunnel"));
	go_Pooka->AddComponent(new GridSnap(DigDug::GetGrid()));
	return go_Pooka;
}

GD::GameObject * DD::DigDugPrefabs::CreateFygar(GD::Scene& scene, GD::ControllerIndex index )
{
	GameObject* go_Fygar = scene.CreateGameObject(static_cast<unsigned int>(Layer::Foreground));
	Texture* fygarTexture = go_Fygar->CreateTexture();
	Sprite* fygarSprite = new Sprite(fygarTexture, "Fygar");
	fygarSprite->AddAnimation(static_cast<unsigned int>(StateID::Idle), Animation{ 1, 0, { {0, 0}, {16.f, 16.f} } });
	fygarSprite->AddAnimation(static_cast<unsigned int>(StateID::Walking), Animation{ 2, 0.25f, { {0, 0}, {32.f, 16.f} } });
	fygarSprite->AddAnimation(static_cast<unsigned int>(StateID::Floating), Animation{ 2, 0.25f, { {48.f, 0}, {80.f, 16.f} } });
	fygarSprite->AddAnimation(static_cast<unsigned int>(StateID::Dying), Animation{ 1, 0, { {80.f, 0}, {96.f, 16.f} } });
	fygarSprite->AddAnimation(static_cast<unsigned int>(StateID::Attacking), Animation{ 1, 0, { {32.f, 0}, {48.f, 16.f} } });
	fygarSprite->AddAnimation(static_cast<unsigned int>(StateID::Charging), Animation{ 2, 0.09f, { {16.f, 0}, {48.f, 16.f} } });
	fygarSprite->AddAnimation(static_cast<unsigned int>(StateID::Pumped), Animation{ 4, 0.5f, { {0, 16.f}, {128.f, 48.f} } });
	Collider* fygarCollider = new Collider(fygarTexture, "enemy", 2.0f);
	go_Fygar->AddComponent(fygarCollider);
	go_Fygar->AddComponent(fygarSprite);

	if (index != ControllerIndex::Any)
	{
		PlayerInputAgent* fygarPlayerAgent = new PlayerInputAgent(ControllerIndex::One);
		fygarPlayerAgent->AssignAxis(ControllerAxis::LeftStickX, new MoveHorizontal());
		fygarPlayerAgent->AssignAxis(ControllerAxis::LeftStickY, new MoveVertical());
		fygarPlayerAgent->AssignButton(ControllerButton::A, ButtonState::Pressed, new Float());
		fygarPlayerAgent->AssignButton(ControllerButton::X, ButtonState::Pressed, new Attack());
		go_Fygar->AddComponent(new Entity(new EnemyBehaviour(), fygarPlayerAgent, new Idle()));
	}
	else
		go_Fygar->AddComponent(new Entity(new EnemyBehaviour(), new FygarAgent(), new Idle()));

	go_Fygar->AddComponent(new Physics(40.f, false, fygarCollider, "tunnel"));
	go_Fygar->AddComponent(new GridSnap(DigDug::GetGrid()));
	return go_Fygar;
}

GD::GameObject* DD::DigDugPrefabs::CreateTunnel(GD::Scene& scene) 
{
	GameObject* go_Tunnel = scene.CreateGameObject(static_cast<unsigned int>(Layer::Tunnel));
	Texture* tunnelTexture = go_Tunnel->CreateTexture();
	go_Tunnel->AddComponent(new Sprite(tunnelTexture, "Tunnel"));
	go_Tunnel->AddComponent(new Collider(tunnelTexture, "tunnel"));
	return go_Tunnel;
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