#include "Precompiled.h"
#include "Framework/Core/Engine.h"

#include "Framework/Core/Subsystem.h"

namespace TUK::Framework
{
	void Engine::Startup()
	{
		instance = this;

		for (Subsystem* subsystem : subsystemsByType)
		{
			subsystem->OnStartup();
		}
	}

	void Engine::Shutdown()
	{
		for (Subsystem* subsystem : subsystemsByType | std::views::reverse)
		{
			subsystem->OnShutdown();
		}

		instance = nullptr;
	}

	Engine& Engine::GetInstance()
	{
		return *instance;
	}

	Engine* Engine::instance = nullptr;
}
