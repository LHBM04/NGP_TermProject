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

	Engine* Engine::GetInstance()
	{
		return static_cast<Engine*>(System::GetInstance());
	}

	void Engine::PreTick()
	{
		for (EngineSubsystem& subsystem : GetSubsystems())
		{
			subsystem.PreTick();
		}
	}

	void Engine::Tick()
	{
		for (auto& subsystem : GetSubsystems())
		{
			subsystem.Tick();
		}
	}

	void Engine::PostTick()
	{
		for (auto& subsystem : GetSubsystems())
		{
			subsystem.PostTick();
		}
	}
}
