#pragma once

#include "Subsystem.hpp"

namespace TUK::Framework
{
	class EngineSubsystem : public Subsystem
	{
		friend class Engine;

	public:
		explicit EngineSubsystem(unsigned short priority) noexcept;
		~EngineSubsystem() noexcept override;

	protected:
		virtual void PreTick();
		virtual void Tick();
		virtual void PostTick();
	};
}