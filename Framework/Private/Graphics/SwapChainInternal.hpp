#pragma once

#include <wrl.h>

#include "Framework/Graphics/SwapChain.hpp"

namespace TUK::Framework
{
	class SwapChainInternal : public SwapChain
	{
	public:
		SwapChainInternal() noexcept;
		~SwapChainInternal() noexcept;

		SwapChainInternal(const SwapChainInternal&) noexcept;
		SwapChainInternal& operator=(const SwapChainInternal&) noexcept;
		
		SwapChainInternal(SwapChainInternal&&) noexcept;
		SwapChainInternal& operator=(SwapChainInternal&&) noexcept;
		
		Microsoft::WRL::ComPtr<IDXGISwapChain> GetDXGISwapChain() const noexcept;

	private:
		Microsoft::WRL::ComPtr<IDXGISwapChain> dxgiSwapChain;
	};
}
