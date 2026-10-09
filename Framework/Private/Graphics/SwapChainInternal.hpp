#pragma once

#include <wrl.h>
#include <dxgi.h>
#include <memory>

#include "Framework/Graphics/SwapChain.hpp"

namespace TUK::Framework
{
	class CommandBuffer;
	class RenderTargetInternal;

	class SwapChainInternal : public SwapChain
	{
	public:
		SwapChainInternal(Microsoft::WRL::ComPtr<IDXGISwapChain> dxgiSwapChain,
			std::unique_ptr<RenderTargetInternal> renderTarget) noexcept;
		~SwapChainInternal() noexcept override;
		/** 소유권을 넘기지 않는 네이티브 객체 접근. */
		[[nodiscard]] explicit operator IDXGISwapChain*() const noexcept
		{
			return GetDXGISwapChain().Get();
		}


		Microsoft::WRL::ComPtr<IDXGISwapChain> GetDXGISwapChain() const noexcept;

		/** Interface Override */
		[[nodiscard]] RenderTarget& GetTarget() const noexcept override;
		void Clear(CommandBuffer& commandBuffer) const override;
		void Present() const override;

	private:
		Microsoft::WRL::ComPtr<IDXGISwapChain> dxgiSwapChain;
		std::unique_ptr<RenderTargetInternal> renderTarget;
	};
}
