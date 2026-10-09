#pragma once

namespace TUK::Framework
{
	class DepthStencil
	{
	public:
		virtual ~DepthStencil() noexcept = default;

		DepthStencil(const DepthStencil&) noexcept = delete;
		DepthStencil& operator=(const DepthStencil&) noexcept = delete;

		DepthStencil(DepthStencil&&) noexcept = delete;
		DepthStencil& operator=(DepthStencil&&) noexcept = delete;

	protected:
		DepthStencil() noexcept = default;
	};
}
