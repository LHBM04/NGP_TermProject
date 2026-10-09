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
		Framework::WindowOptions options{};
		options.title = L"Virus Striker";
		options.position = Framework::Vector2D(100, 100);
		options.size = Framework::Vector2D(1280, 960);
		options.isFullscreen = false;
		options.isBorderless = false;
		options.isResizable = false;

		Framework::WindowSubsystem* windowSubsystem = MyEngine::GetInstance()->GetSubsystem<Framework::WindowSubsystem>();
		if (windowSubsystem)
		{
			auto windowResult = windowSubsystem->Create(options);
			if (!windowResult)
			{
				ReportError(windowResult.error());
				return;
			}

			Framework::RenderSubsystem* renderSubsystem = MyEngine::GetInstance()->GetSubsystem<Framework::RenderSubsystem>();
			if (renderSubsystem)
			{
				renderSubsystem->RegisterWindow(windowResult.value());
			}
			else
			{
				ReportError("RenderSubsystem not found.");
				return;
			}
		}
		else
		{
			ReportError("WindowSubsystem not found.");
			return;
		}
	}
}
