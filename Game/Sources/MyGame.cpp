#include "Precompiled.hpp"
#include "MyGame.hpp"
#include "MyEngine.hpp"

DEFINE_GAME_INSTANCE(::TUK::Game::MyGame)

namespace TUK::Game
{
	MyGame::MyGame() noexcept
	{
	}

	MyGame::~MyGame() noexcept
	{
	}

	void MyGame::Ready()
	{
		RequireWindow();
	}

	void MyGame::RequireWindow()
	{
		WindowOptions options{};
		options.title = L"Virus Striker";
		options.position = Framework::Vector2D(100, 100);
		options.size = Framework::Vector2D(1280, 960);
		options.isFullscreen = false;
		options.isBorderless = false;
		options.isResizable = false;

		WindowSubsystem* windowSubsystem = MyEngine::GetInstance()->GetSubsystem<WindowSubsystem>();
		assert(windowSubsystem);

		window = windowSubsystem->Create(options).value_or(nullptr);
		assert(window);

		RenderSubsystem* renderSubsystem = MyEngine::GetInstance()->GetSubsystem<RenderSubsystem>();
		assert(renderSubsystem);

		renderSubsystem->RegisterWindow(*window);
	}

	void MyGame::RequireScenes()
	{
		SceneSubsystem* sceneSubsystem = AddSubsystem<SceneSubsystem>();
		assert(sceneSubsystem);

		sceneSubsystem->AddScene<Scene_Stage1>(0, L"Stage1");
	}
}
