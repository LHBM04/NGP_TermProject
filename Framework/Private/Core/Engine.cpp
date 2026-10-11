#include "Precompiled.hpp"
#include "Framework/Core/Engine.hpp"

#include "Framework/Core/Game.hpp"

namespace TUK::Framework
{
	Engine* Engine::instance = nullptr;

	Engine::Engine() noexcept
	{
		assert(!instance);
		instance = this;
	}

	Engine::~Engine() noexcept
	{
		if (instance == this)
		{
			instance = nullptr;
		}
	}

	Engine* Engine::GetInstance()
	{
		assert(instance);
		return instance;
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
