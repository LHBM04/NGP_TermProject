#pragma once

namespace TUK::Framework
{
	class CommandBuffer;
	class RenderTarget;

	class SwapChain
	{
	public:
		virtual ~SwapChain() noexcept = default;

		SwapChain(const SwapChain&) noexcept = delete;
		SwapChain& operator=(const SwapChain&) noexcept = delete;

		SwapChain(SwapChain&&) noexcept = delete;
		SwapChain& operator=(SwapChain&&) noexcept = delete;

		/** 백 버퍼를 가리키는 타깃. 스왑 체인이 수명을 소유한다. */
		[[nodiscard]] virtual RenderTarget& GetTarget() const noexcept = 0;
		virtual void Clear(CommandBuffer& commandBuffer) const = 0;
		virtual void Present() const = 0;

	protected:
		SwapChain() noexcept = default;
	};
}
