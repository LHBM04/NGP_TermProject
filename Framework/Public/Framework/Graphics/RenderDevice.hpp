#pragma once 

#include <memory>

namespace TUK::Framework
{
	class Buffer;
	class CommandBuffer;
	class Texture;
	class RenderTarget;
	class SwapChain;
	class Window;
	
	class RenderDevice
	{
	public:
		virtual ~RenderDevice() noexcept = default;

		RenderDevice(const RenderDevice&) noexcept = delete;
		RenderDevice& operator=(const RenderDevice&) noexcept = delete;
		
		RenderDevice(RenderDevice&&) noexcept = delete;
		RenderDevice& operator=(RenderDevice&&) noexcept = delete;

		/** 명령 제출 */
		virtual void Submit(const CommandBuffer& commandBuffer) const = 0;

		/** 스왑 체인 생성 */
		[[nodiscard]] virtual std::unique_ptr<SwapChain> CreateSwapChain(const Window& window) const = 0;

		/** 버퍼 생성 */
		[[nodiscard]] virtual std::unique_ptr<Buffer> CreateBuffer(size_t size) const = 0;

		/** 텍스쳐 생성 */
		[[nodiscard]] virtual std::unique_ptr<Texture> CreateTexture() const = 0;

		/** 렌더 타겟 생성 */
		[[nodiscard]] virtual std::unique_ptr<RenderTarget> CreateTarget() const = 0;

	protected:
		RenderDevice() noexcept = default;
	};
}
