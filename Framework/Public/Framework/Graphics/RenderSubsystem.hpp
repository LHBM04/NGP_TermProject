#pragma once

#include "../Core/EngineSubsystem.hpp"

#include <memory>
#include <unordered_map>

namespace TUK::Framework
{
	class CommandBuffer;
	class SwapChain;
	class RenderDevice;
	class Window;

	class RenderSubsystem : public EngineSubsystem
	{
	public:
		RenderSubsystem() noexcept;
		~RenderSubsystem() noexcept override;

		/** 창 등록 */
		void RegisterWindow(const Window& window);

		/** 창 파괴 전에 호출한다. 등록되지 않은 창은 무시한다. */
		void UnregisterWindow(const Window& window);

		/** 디바이스 Getter */
		[[nodiscard]] RenderDevice* GetDevice() const noexcept;

		/** 명령 리스트 Getter */
		[[nodiscard]] CommandBuffer* GetCommandBuffer() const noexcept;

	protected:
		void OnStartup() override;
		void OnShutdown() override;

		void PreTick() override;
		void PostTick() override;

	private:
		/** 디바이스 */
		std::unique_ptr<RenderDevice> device;

		/** 명령 리스트 */
		std::unique_ptr<CommandBuffer> commandBuffer;

		/** 창은 소유하지 않으며 연결된 스왑 체인만 소유한다. */
		std::unordered_map<const Window*, std::unique_ptr<SwapChain>> swapChains;
	};
}
