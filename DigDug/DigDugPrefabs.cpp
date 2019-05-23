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
	GameObject* go_Button = scene.CreateGameObject();
	Texture* onTexture = go_Button->CreateTexture(RenderMode::center);
	Texture* offTexture = go_Button->CreateTexture(RenderMode::center);
	go_Button->AddComponent(new HudText(onTexture, std::move(text), std::move(font), onColor));
	go_Button->AddComponent(new HudText(offTexture, std::move(text), std::move(font), offColor));
	go_Button->AddComponent(new MenuButton(offTexture, onTexture, command));
	return go_Button;
}

GD::GameObject * DD::DigDugPrefabs::CreateDigDug(GD::Scene& scene, GD::ControllerIndex index )
{
	GameObject* go_DigDug = scene.CreateGameObject();
	Texture* digDugTexture = go_DigDug->CreateTexture();
	Sprite* digDugSprite = new Sprite(digDugTexture, "DigDug");
	digDugSprite->AddAnimation(static_cast<unsigned int>(StateID::Idle), Animation{ 1, 0, { {0, 0}, {16.f, 16.f} } });
	digDugSprite->AddAnimation(static_cast<unsigned int>(StateID::Walking), Animation{ 2, 0.15f, { {0, 0}, {32.f, 16.f} } });
	digDugSprite->AddAnimation(static_cast<unsigned int>(StateID::Dying), Animation{ 5, 0.3f, { {0, 16.f}, {80.f, 32.f} }, false });
	digDugSprite->AddAnimation(static_cast<unsigned int>(StateID::Attacking), Animation{ 1, 0, { {0, 32.f}, {16.f, 48.f} } });
	go_DigDug->AddComponent(new Collider(digDugTexture, "player"));
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
	GameObject* go_Pooka = scene.CreateGameObject();
	Texture* pookaTexture = go_Pooka->CreateTexture();
	Sprite* pookaSprite = new Sprite(pookaTexture, "Pooka");
	pookaSprite->AddAnimation(static_cast<unsigned int>(StateID::Idle), Animation{ 1, 0, { {0, 0}, {16.f, 16.f} } });
	pookaSprite->AddAnimation(static_cast<unsigned int>(StateID::Walking), Animation{ 2, 0.25f, { {0, 0}, {32.f, 16.f} } });
	pookaSprite->AddAnimation(static_cast<unsigned int>(StateID::Floating), Animation{ 2, 0.25f, { {48.f, 0}, {80.f, 16.f} } });
	pookaSprite->AddAnimation(static_cast<unsigned int>(StateID::Dying), Animation{ 1, 0, { {80.f, 0}, {96.f, 16.f} } });
	go_Pooka->AddComponent(new Collider(pookaTexture, "enemy"));
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

	go_Pooka->AddComponent(new Physics(40.f));
	go_Pooka->AddComponent(new GridSnap(DigDug::GetGrid()));
	return go_Pooka;
}

GD::GameObject * DD::DigDugPrefabs::CreateFygar(GD::Scene& scene, GD::ControllerIndex index )
{
	GameObject* go_Fygar = scene.CreateGameObject();
	Texture* fygarTexture = go_Fygar->CreateTexture();
	Sprite* fygarSprite = new Sprite(fygarTexture, "Fygar");
	fygarSprite->AddAnimation(static_cast<unsigned int>(StateID::Idle), Animation{ 1, 0, { {0, 0}, {16.f, 16.f} } });
	fygarSprite->AddAnimation(static_cast<unsigned int>(StateID::Walking), Animation{ 2, 0.25f, { {0, 0}, {32.f, 16.f} } });
	fygarSprite->AddAnimation(static_cast<unsigned int>(StateID::Floating), Animation{ 2, 0.25f, { {48.f, 0}, {80.f, 16.f} } });
	fygarSprite->AddAnimation(static_cast<unsigned int>(StateID::Dying), Animation{ 1, 0, { {80.f, 0}, {96.f, 16.f} } });
	fygarSprite->AddAnimation(static_cast<unsigned int>(StateID::Attacking), Animation{ 1, 0, { {32.f, 0}, {48.f, 16.f} } });
	fygarSprite->AddAnimation(static_cast<unsigned int>(StateID::Charging), Animation{ 2, 0.09f, { {16.f, 0}, {48.f, 16.f} } });
	go_Fygar->AddComponent(new Collider(fygarTexture, "enemy"));
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

	go_Fygar->AddComponent(new Physics(40.f));
	go_Fygar->AddComponent(new GridSnap(DigDug::GetGrid()));
	return go_Fygar;
}
