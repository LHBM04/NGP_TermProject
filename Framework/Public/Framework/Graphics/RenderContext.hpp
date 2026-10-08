#pragma once

namespace TUK::Framework
{
	class RenderContext
	{
	public:
		RenderContext() noexcept;
		~RenderContext() noexcept;

		RenderContext(const RenderContext&) noexcept;
		RenderContext& operator=(const RenderContext&) noexcept;

		RenderContext(RenderContext&&) noexcept;
		RenderContext& operator=(RenderContext&&) noexcept;
	};
}
