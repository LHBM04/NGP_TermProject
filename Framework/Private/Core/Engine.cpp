#include "Precompiled.hpp"
#include "Framework/Core/Engine.hpp"

#include "Framework/Core/Game.hpp"

namespace TUK::Framework
{
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

	Engine* Engine::GetInstance()
	{
		return static_cast<Engine*>(System::GetInstance());
	}
}
