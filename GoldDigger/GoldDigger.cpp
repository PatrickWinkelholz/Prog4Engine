#include "GoldDiggerPCH.h"
#include "GoldDigger.h"
#include <chrono>
#include <thread>
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include <SDL.h>
#include "Texture.h"
#include "GameObject.h"
#include "Scene.h"
#include "HudText.h"
#include "FPSCounter.h"

void engine::GoldDigger::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		640,
		480,
		SDL_WINDOW_OPENGL
	);
	if (window == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(window);

	// tell the resource manager where he can find the game data
	ResourceManager::GetInstance().Init("../Data/");

	LoadGame();

	SceneManager::GetInstance().Initialize();
}

/**
 * Code constructing the scene world starts here
 */
void engine::GoldDigger::LoadGame()
{
	LoadResources();
	
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

void engine::GoldDigger::LoadResources() 
{
	//loading fonts
	ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);

	//loading textures
	ResourceManager::GetInstance().LoadTexture("logo.png");
	ResourceManager::GetInstance().LoadTexture("background.jpg");
}

void engine::GoldDigger::Cleanup()
{
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(window);
	window = nullptr;
	SDL_Quit();
}

void engine::GoldDigger::Run()
{
	static float msPerUpdate = 0.02f;

	Initialize();
	{
		auto t = std::chrono::high_resolution_clock::now();
		auto& renderer = Renderer::GetInstance();
		auto& sceneManager = SceneManager::GetInstance();
		auto& input = InputManager::GetInstance();

		bool doContinue = true;
		auto lastTime = std::chrono::high_resolution_clock::now();
		float lag = 0.0f;
		while (doContinue)
		{
			const auto currentTime = std::chrono::high_resolution_clock::now();
			float deltaTime = std::chrono::duration<float>(currentTime - lastTime).count();
			lastTime = currentTime;
			lag += deltaTime;
			doContinue = input.ProcessInput();
			while (lag >= msPerUpdate) 
			{
				sceneManager.FixedUpdate();
				lag -= msPerUpdate;
			}
			sceneManager.Update( deltaTime );
			renderer.Render(lag / msPerUpdate);

			t += std::chrono::milliseconds(msPerFrame);
			std::this_thread::sleep_until(t);
		}
	}

	Cleanup();
}
