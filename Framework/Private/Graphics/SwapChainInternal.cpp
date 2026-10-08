#include "Precompiled.hpp"
#include "Graphics/SwapChainInternal.hpp"

namespace TUK::Framework
{
	SwapChainInternal::SwapChainInternal() noexcept
		: dxgiSwapChain(nullptr)
	{
	}

	SwapChainInternal::~SwapChainInternal() noexcept
	{
		if (dxgiSwapChain)
		{
			dxgiSwapChain.Reset();
			dxgiSwapChain = nullptr;
		}
	}

	SwapChainInternal::SwapChainInternal(const SwapChainInternal&) noexcept
		= default;

	SwapChainInternal& SwapChainInternal::operator=(const SwapChainInternal&) noexcept
		= default;

	SwapChainInternal::SwapChainInternal(SwapChainInternal&&) noexcept
		= default;

	SwapChainInternal& SwapChainInternal::operator=(SwapChainInternal&&) noexcept
		= default;

	Microsoft::WRL::ComPtr<IDXGISwapChain> SwapChainInternal::GetDXGISwapChain() const noexcept
	{
		return dxgiSwapChain;
	}
}
