#pragma once

#include "TextureFormat.hpp"

namespace TUK::Framework
{
	class RenderTarget
	{
	public:
		virtual ~RenderTarget() noexcept = default;

		RenderTarget(const RenderTarget&) noexcept = delete;
		RenderTarget& operator=(const RenderTarget&) noexcept = delete;

		RenderTarget(RenderTarget&&) noexcept = delete;
		RenderTarget& operator=(RenderTarget&&) noexcept = delete;

		/** 너비 Getter */
		[[nodiscard]] virtual int GetWidth() const noexcept = 0;

		/** 높이 Getter */
		[[nodiscard]] virtual int GetHeight() const noexcept = 0;
		
		/** 포맷 Getter */
		[[nodiscard]] virtual TextureFormat GetFormat() const noexcept = 0;

	protected:
		RenderTarget() noexcept = default;
	};
}
