#include "Precompiled.hpp"
#include "Framework/Graphics/RenderSubsystem.hpp"

#include "Graphics/RenderDeviceInternal.hpp"

namespace TUK::Framework
{
	RenderSubsystem::RenderSubsystem() noexcept
		: EngineSubsystem(20)
	{	
	}

	RenderSubsystem::~RenderSubsystem() noexcept
	{
		if (device)
		{
			device.reset();
			device = nullptr;
		}
	}

	void RenderSubsystem::OnStartup()
	{
		device = std::make_unique<RenderDeviceInternal>();
	}

	void RenderSubsystem::OnShutdown()
	{
		if (device)
		{
			device.reset();
			device = nullptr;
		}
	}
}
