#pragma once

namespace TUK::Framework
{
	class SwapChain
	{
	public:
		SwapChain() noexcept;
		~SwapChain() noexcept;

		SwapChain(const SwapChain&) noexcept;
		SwapChain& operator=(const SwapChain&) noexcept;

		SwapChain(SwapChain&&) noexcept;
		SwapChain& operator=(SwapChain&&) noexcept;
	};
}
