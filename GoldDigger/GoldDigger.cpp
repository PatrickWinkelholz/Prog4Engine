#include "GoldDiggerPCH.h"
#include "GoldDigger.h"
#include <chrono>
#include <thread>
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "GoldDiggerGame.h"
#include <ctime>

GD::GoldDigger::GoldDigger(GoldDiggerGame* game)
	: m_Game{ game }
{}

void GD::GoldDigger::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	if (!m_Game)
		throw std::exception{"GoldDigger initialization error, game not set!"};

	window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		int(m_Game->m_Dimensions.x * m_Game->m_GameScale),
		int(m_Game->m_Dimensions.y * m_Game->m_GameScale),
		SDL_WINDOW_OPENGL
	);

	if (window == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(window, m_Game->m_GameScale);

	m_Game->Initialize();
}

void GD::GoldDigger::Cleanup()
{
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(window);
	window = nullptr;
	SDL_Quit();
}

void GD::GoldDigger::Run()
{
	srand(unsigned int(time(nullptr)));
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
			while (lag >= m_Game->m_MsPerUpdate) 
			{
				sceneManager.FixedUpdate();
				lag -= m_Game->m_MsPerUpdate;
			}
			sceneManager.Update( deltaTime );
			renderer.Render(lag / m_Game->m_MsPerUpdate);
			t += std::chrono::milliseconds(m_Game->m_MsPerFrame);
			std::this_thread::sleep_until(t);
		}
	}

	Cleanup();
}
