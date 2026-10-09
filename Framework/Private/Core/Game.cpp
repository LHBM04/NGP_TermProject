#include "Precompiled.hpp"
#include "Framework/Core/Game.hpp"

#include "Framework/Core/Engine.hpp"

#include "Framework/Platform/TimeSubsystem.hpp"
#include "Framework/Platform/WindowSubsystem.hpp"

namespace TUK::Framework
{
	Game::Game(const WindowOptions& windowOptions)
		: windowOptions(windowOptions)
	{
	}

	Game::~Game() noexcept
	{
	}

	void Game::Startup()
	{
		Ready();
		if (GetQuitCode() != EXIT_SUCCESS) return;
		System::Startup();
	}

	void Game::OnReady()
	{
	}

	void Game::SetWindowOptions(const WindowOptions& windowOptions)
	{
		this->windowOptions = windowOptions;
	}

	Game* Game::GetInstance()
	{
		Game* game = Engine::GetInstance()->game;
		assert(game);
		return game;
	}

	void Game::Tick()
	{
		TimeSubsystem* time = Engine::GetInstance()->GetSubsystem<TimeSubsystem>();
		assert(time);

		for (auto& subsystem : GetSubsystems())
		{
			subsystem.EarlyUpdate();
		}

		while (time->ShouldFixedStep())
		{
			for (auto& subsystem : GetSubsystems())
			{
				subsystem.FixedUpdate();
			}
		}

		for (auto& subsystem : GetSubsystems())
		{
			subsystem.Update();
		}

		for (auto& subsystem : GetSubsystems())
		{
			subsystem.LateUpdate();
		}
	}
}
