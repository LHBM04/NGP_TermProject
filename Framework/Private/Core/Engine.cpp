#include "Precompiled.hpp"
#include "Framework/Core/Engine.hpp"

#include "Framework/Core/Game.hpp"

namespace TUK::Framework
{
	Engine::Engine() noexcept
	{
	}

	Engine::~Engine() noexcept
	{
	}

	void Engine::OnReady()
	{
	}

	int Engine::Run(Game& game)
	{
		this->game = &game;

		Startup();

		if (IsRunning())
		{
			game.Startup();

			if (!game.IsRunning())
			{
				RequestQuit(game.GetQuitCode());
			}

			while (IsRunning())
			{
				PreTick();
				Tick();
				PostTick();

				if (!game.IsRunning())
				{
					RequestQuit(game.GetQuitCode());
				}
			}

			game.Shutdown();

			if (game.GetQuitCode() != EXIT_SUCCESS)
			{
				RequestQuit(game.GetQuitCode());
			}
		}

		Shutdown();
		this->game = nullptr;
		return GetQuitCode();
	}

	void Engine::PreTick()
	{
		for (auto& subsystem : GetSubsystems<EngineSubsystem>())
		{
			subsystem.PreTick();
		}
	}

	void Engine::Tick()
	{
		for (auto& subsystem : GetSubsystems<EngineSubsystem>())
		{
			subsystem.Tick();
		}

		if (IsRunning())
		{
			game->Tick();
		}
	}

	void Engine::PostTick()
	{
		for (auto& subsystem : GetSubsystems<EngineSubsystem>())
		{
			subsystem.PostTick();
		}
	}

	Engine* Engine::GetInstance()
	{
		return static_cast<Engine*>(System::GetInstance());
	}
}
