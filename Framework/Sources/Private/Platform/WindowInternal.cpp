#include "Precompiled.h"
#include "WindowInternal.h"

namespace TUK::Framework
{
	WindowInternal::WindowInternal(HWND hWnd)
		: hWnd(hWnd)
	{
	}

	WindowInternal::~WindowInternal()
	{
		if (hWnd)
		{
			DestroyWindow(hWnd);
			hWnd = nullptr;
		}
	}

	std::wstring WindowInternal::GetTitle() const noexcept
	{
		int length = GetWindowTextLengthW(hWnd);
		std::wstring title(length, L'\0');
		GetWindowTextW(hWnd, title.data(), length + 1);
		return title;
	}

	void WindowInternal::SetTitle(std::wstring_view title) noexcept
	{
		SetWindowTextW(hWnd, title.data());
	}

	int WindowInternal::GetSizeX() const noexcept
	{
		RECT rect;
		GetWindowRect(hWnd, &rect);
		return rect.right - rect.left;
	}

	void WindowInternal::SetSizeX(int sizeX) noexcept
	{
		RECT rect;
		GetWindowRect(hWnd, &rect);
		SetWindowPos(hWnd, nullptr, rect.left, rect.top, sizeX, rect.bottom - rect.top, SWP_NOZORDER | SWP_NOMOVE);
	}

	int WindowInternal::GetSizeY() const noexcept
	{
		RECT rect;
		GetWindowRect(hWnd, &rect);
		return rect.bottom - rect.top;
	}

	void WindowInternal::SetSizeY(int sizeY) noexcept
	{
		RECT rect;
		GetWindowRect(hWnd, &rect);
		SetWindowPos(hWnd, nullptr, rect.left, rect.top, rect.right - rect.left, sizeY, SWP_NOZORDER | SWP_NOMOVE);
	}

	int WindowInternal::GetPositionX() const noexcept
	{
		RECT rect;
		GetWindowRect(hWnd, &rect);
		return rect.left;
	}

	void WindowInternal::SetPositionX(int positionX) noexcept
	{
		RECT rect;
		GetWindowRect(hWnd, &rect);
		SetWindowPos(hWnd, nullptr, positionX, rect.top, rect.right - rect.left, rect.bottom - rect.top, SWP_NOZORDER | SWP_NOSIZE);
	}

	int WindowInternal::GetPositionY() const noexcept
	{
		RECT rect;
		GetWindowRect(hWnd, &rect);
		return rect.top;
	}

	void WindowInternal::SetPositionY(int positionY) noexcept
	{
		RECT rect;
		GetWindowRect(hWnd, &rect);
		SetWindowPos(hWnd, nullptr, rect.left, positionY, rect.right - rect.left, rect.bottom - rect.top, SWP_NOZORDER | SWP_NOSIZE);
	}

	HWND WindowInternal::GetHWND() const noexcept
	{
		return hWnd;
	}
}
