#include "Precompiled.hpp"
#include "Framework/Core/Game.hpp"

#include "Framework/Core/Engine.hpp"

#include "Framework/Platform/TimeSubsystem.hpp"

namespace TUK::Framework
{
	Game* Game::GetInstance()
	{
		return static_cast<Game*>(System::GetInstance());
	}

	void Game::Tick()
	{
		for (GameSubsystem& subsystem : GetSubsystems())
		{
			subsystem.EarlyUpdate();
		}

		// 시간이 있을 때만 가능해야 함.
		// 근데 Game이 TimeSubsystem을 알고 있어야 하는 게 맘에 안 듦.
		if (TimeSubsystem* const time = Engine::GetInstance()->GetSubsystem<TimeSubsystem>())
		{
			while (time->ShouldFixedStep())
			{
				for (GameSubsystem& subsystem : GetSubsystems())
				{
					subsystem.FixedUpdate();
				}
			}
		}

		for (GameSubsystem& subsystem : GetSubsystems())
		{
			subsystem.Update();
		}

		for (GameSubsystem& subsystem : GetSubsystems())
		{
			subsystem.LateUpdate();
		}
	}
}
