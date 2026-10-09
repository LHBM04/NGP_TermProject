#pragma once

#include <string>
#include <string_view>

#include "../Math/Vector2D.hpp"

namespace TUK::Framework
{
	class Window
	{
	public:
		virtual ~Window() noexcept = default;

		Window(const Window&) = delete;
		Window& operator=(const Window&) = delete;

		Window(Window&&) = delete;
		Window& operator=(Window&&) = delete;

		[[nodiscard]] virtual std::wstring GetTitle() const = 0;
		virtual void SetTitle(std::wstring_view title) = 0;

		[[nodiscard]] virtual Vector2D<int> GetPosition() const noexcept = 0;
		virtual void SetPosition(const Vector2D<int>& position) noexcept = 0;

		[[nodiscard]] virtual Vector2D<int> GetSize() const noexcept = 0;
		virtual void SetSize(const Vector2D<int>& size) noexcept = 0;

		[[nodiscard]] virtual bool IsResizable() const noexcept = 0;
		[[nodiscard]] virtual bool IsBorderless() const noexcept = 0;
		[[nodiscard]] virtual bool IsFullscreen() const noexcept = 0;

		[[nodiscard]] virtual bool ShouldClose() const noexcept = 0;
		virtual void RequestClose() noexcept = 0;

	protected:
		Window() noexcept = default;
	};
}
