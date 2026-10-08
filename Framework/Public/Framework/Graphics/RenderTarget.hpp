#pragma once

namespace TUK::Framework
{
	class RenderTarget
	{
	public:
		RenderTarget() noexcept;
		virtual ~RenderTarget() noexcept;

		RenderTarget(const RenderTarget&) noexcept;
		RenderTarget& operator=(const RenderTarget&) noexcept;

		RenderTarget(RenderTarget&&) noexcept;
		RenderTarget& operator=(RenderTarget&&) noexcept;
	};
}
