#pragma once

#include "../Core/EngineSubsystem.hpp"

#include "RenderDevice.hpp"

namespace TUK::Framework
{
	class RenderSubsystem : public EngineSubsystem
	{
	public:
		RenderSubsystem() noexcept;
		~RenderSubsystem() noexcept override;

		void OnStartup() override;
		void OnShutdown() override;

		/** 디바이스 Getter */
		[[nodiscard]] RenderDevice* GetDevice() const noexcept;

	private:
		std::unique_ptr<RenderDevice> device;
	};
}
