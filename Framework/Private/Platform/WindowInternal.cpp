#include "Precompiled.hpp"
#include "Platform/WindowInternal.hpp"

#include <stdexcept>

namespace TUK::Framework
{
	WindowInternal::WindowInternal() noexcept
		: hWnd(nullptr)
		, shouldClose(false)
	{
	}

	WindowInternal::~WindowInternal() noexcept
	{
		if (hWnd)
		{
			DestroyWindow(hWnd);
			hWnd = nullptr;
		}
	}

	WindowInternal::operator HWND() const noexcept
	{
		return GetHWND();
	}

	std::wstring WindowInternal::GetTitle() const
	{
		const int length = GetWindowTextLengthW(hWnd);
		if (length == 0)
		{
			return {};
		}
		if (length == std::numeric_limits<int>::max())
		{
			throw std::length_error("Window title exceeds the Win32 text buffer limit.");
		}
		std::wstring title(static_cast<std::size_t>(length) + 1, L'\0');
		const int copied = GetWindowTextW(hWnd, title.data(), length + 1);
		title.resize(static_cast<std::size_t>(copied));
		return title;
	}

	void WindowInternal::SetTitle(std::wstring_view title)
	{
		const std::wstring windowTitle(title);
		SetWindowTextW(hWnd, windowTitle.c_str());
	}

	Vector2D<int> WindowInternal::GetPosition() const noexcept
	{
		RECT rect{};
		if (!GetWindowRect(hWnd, &rect))
		{
			return {};
		}
		return { rect.left, rect.top };
	}

	void WindowInternal::SetPosition(const Vector2D<int>& position) noexcept
	{
		SetWindowPos(hWnd, nullptr, position.GetX(), position.GetY(), 0, 0, SWP_NOSIZE | SWP_NOZORDER);
	}

	Vector2D<int> WindowInternal::GetSize() const noexcept
	{
		RECT rect{};
		if (!GetWindowRect(hWnd, &rect))
		{
			return {};
		}
		return { rect.right - rect.left, rect.bottom - rect.top };
	}

	void WindowInternal::SetSize(const Vector2D<int>& size) noexcept
	{
		SetWindowPos(hWnd, nullptr, 0, 0, size.GetX(), size.GetY(), SWP_NOMOVE | SWP_NOZORDER);
	}

	HWND WindowInternal::GetHWND() const noexcept
	{
		return hWnd;
	}

	bool WindowInternal::IsResizable() const noexcept
	{
		return hWnd && (GetWindowLongPtrW(hWnd, GWL_STYLE) & WS_THICKFRAME) != 0;
	}

	bool WindowInternal::IsBorderless() const noexcept
	{
		return hWnd && (GetWindowLongPtrW(hWnd, GWL_STYLE) & WS_CAPTION) == 0;
	}

	bool WindowInternal::IsFullscreen() const noexcept
	{
		if (!IsBorderless() || IsIconic(hWnd))
		{
			return false;
		}
		RECT rect{};
		MONITORINFO monitor{};
		monitor.cbSize = sizeof(monitor);
		if (!GetWindowRect(hWnd, &rect)
			|| !GetMonitorInfoW(MonitorFromWindow(hWnd, MONITOR_DEFAULTTONEAREST), &monitor))
		{
			return false;
		}
		return EqualRect(&rect, &monitor.rcMonitor) != FALSE;
	}

	bool WindowInternal::ShouldClose() const noexcept
	{
		return shouldClose;
	}

	void WindowInternal::RequestClose() noexcept
	{
		shouldClose = true;
	}

	LRESULT WindowInternal::HandleMessage(HWND handle, UINT message, WPARAM wParam, LPARAM lParam) noexcept
	{
		switch (message)
		{
			case WM_NCCREATE:
			{
				hWnd = handle;
				return DefWindowProcW(handle, message, wParam, lParam);
			}
			case WM_NCCALCSIZE:
			{
				if (IsBorderless())
				{
					return 0;
				}
				return DefWindowProcW(handle, message, wParam, lParam);
			}
			case WM_GETMINMAXINFO:
			{
				if (IsBorderless() && !IsFullscreen())
				{
					MONITORINFO monitor{};
					monitor.cbSize = sizeof(monitor);
					if (GetMonitorInfoW(MonitorFromWindow(handle, MONITOR_DEFAULTTONEAREST), &monitor))
					{
						auto& bounds = *reinterpret_cast<MINMAXINFO*>(lParam);
						bounds.ptMaxPosition = { monitor.rcWork.left - monitor.rcMonitor.left,
							monitor.rcWork.top - monitor.rcMonitor.top };
						bounds.ptMaxSize = { monitor.rcWork.right - monitor.rcWork.left,
							monitor.rcWork.bottom - monitor.rcWork.top };
						return 0;
					}
				}
				return DefWindowProcW(handle, message, wParam, lParam);
			}
			case WM_NCHITTEST:
			{
				if (IsBorderless() && !IsFullscreen() && IsResizable() && !IsZoomed(handle))
				{
					RECT rect{};
					if (GetWindowRect(handle, &rect))
					{
						const UINT dpi = GetDpiForWindow(handle);
						const int borderX = GetSystemMetricsForDpi(SM_CXSIZEFRAME, dpi)
							+ GetSystemMetricsForDpi(SM_CXPADDEDBORDER, dpi);
						const int borderY = GetSystemMetricsForDpi(SM_CYSIZEFRAME, dpi)
							+ GetSystemMetricsForDpi(SM_CXPADDEDBORDER, dpi);
						const int x = GET_X_LPARAM(lParam);
						const int y = GET_Y_LPARAM(lParam);
						const bool isLeft = x < rect.left + borderX;
						const bool isRight = x >= rect.right - borderX;
						const bool isTop = y < rect.top + borderY;
						const bool isBottom = y >= rect.bottom - borderY;
						if (isTop)
						{
							return isLeft ? HTTOPLEFT : isRight ? HTTOPRIGHT : HTTOP;
						}
						if (isBottom)
						{
							return isLeft ? HTBOTTOMLEFT : isRight ? HTBOTTOMRIGHT : HTBOTTOM;
						}
						if (isLeft)
						{
							return HTLEFT;
						}
						if (isRight)
						{
							return HTRIGHT;
						}
						return HTCLIENT;
					}
				}
				return DefWindowProcW(handle, message, wParam, lParam);
			}
			case WM_CLOSE:
			{
				RequestClose();
				return 0;
			}
			case WM_NCDESTROY:
			{
				hWnd = nullptr;
				RequestClose();
				return 0;
			}
			default:
			{
				return DefWindowProcW(handle, message, wParam, lParam);
			}
		}

		std::unreachable();
	}
}
