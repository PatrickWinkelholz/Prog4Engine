#include "pch.h"
#include <memory>
#include <string>
#include <SDL.h>

#include "DigDug.h"

//#include "InputManager.h"
#include "ResourceManager.h"
#include "FPSCounter.h"
#include "HudText.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Texture.h"
#include "GameObject.h"

using namespace GD;

DigDug::DigDug() 
{

}

DigDug::~DigDug()
{

}

void DigDug::LoadGame() 
{
	const std::string sceneName{ "test" };
	Scene& scene = SceneManager::GetInstance().CreateScene(sceneName);

	std::shared_ptr<GameObject> go_Background = std::make_shared<GameObject>();
	go_Background->AddComponent(new Texture("background"));
	scene.Add(go_Background);

	std::shared_ptr<GameObject> go_Logo = std::make_shared<GameObject>();
	go_Logo->AddComponent(new Texture("logo"));
	go_Logo->SetPosition(216, 180);
	scene.Add(go_Logo);

	std::shared_ptr<GameObject> go_Headline = std::make_shared<GameObject>();
	go_Headline->AddComponent(new HudText("Programming 4 Assignment", "Lingua"));
	go_Headline->SetPosition(80, 30);
	scene.Add(go_Headline);

	std::shared_ptr<GameObject> go_FPSCounter = std::make_shared<GameObject>();
	go_FPSCounter->AddComponent(new FPSCounter());
	scene.Add(go_FPSCounter);
}

void DigDug::LoadResources()
{
	//loading fonts
	ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);

	//loading textures
	ResourceManager::GetInstance().LoadTexture("logo.png");
	ResourceManager::GetInstance().LoadTexture("background.jpg");
}