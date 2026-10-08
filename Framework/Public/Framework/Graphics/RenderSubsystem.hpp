#pragma once

#include "../Core/EngineSubsystem.hpp"

namespace TUK::Framework
{
	class RenderSubsystem : public EngineSubsystem
	{
	public:
		RenderSubsystem() noexcept;
		~RenderSubsystem() noexcept override;
	};
}
