#pragma once

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <windows.h>

#include "Framework/Platform/Window.hpp"

namespace TUK::Framework
{
	class WindowInternal final : public Window
	{
	public:
		WindowInternal() noexcept;
		~WindowInternal() noexcept override;
		
		[[nodiscard]] explicit operator HWND() const noexcept;

		[[nodiscard]] std::wstring GetTitle() const override;
		void SetTitle(std::wstring_view title) override;

		[[nodiscard]] Vector2D<int> GetPosition() const noexcept override;
		void SetPosition(const Vector2D<int>& position) noexcept override;

		[[nodiscard]] Vector2D<int> GetSize() const noexcept override;
		void SetSize(const Vector2D<int>& size) noexcept override;

		[[nodiscard]] bool IsResizable() const noexcept override;
		[[nodiscard]] bool IsBorderless() const noexcept override;
		[[nodiscard]] bool IsFullscreen() const noexcept override;

		[[nodiscard]] bool ShouldClose() const noexcept override;
		void RequestClose() noexcept override;

		[[nodiscard]] HWND GetHWND() const noexcept;
		LRESULT HandleMessage(HWND handle, UINT message, WPARAM wParam, LPARAM lParam) noexcept;

	private:
		HWND hWnd;
		bool shouldClose;
	};
}
