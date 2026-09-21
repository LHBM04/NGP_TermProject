#include "Precompiled.h"
#include "Framework/Platform/WindowSubsystem.h"

#include "Framework/Platform/Window.h"
#include "Framework/Platform/WindowFlags.h"
#include "Framework/Platform/WindowOptions.h"

#include "Platform/WindowInternal.h"

namespace TUK::Framework
{
	LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		switch (uMsg)
		{
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
		default:
			return DefWindowProcW(hWnd, uMsg, wParam, lParam);
		}
	}

	void WindowSubsystem::OnStartup()
	{
		ZeroMemory(&wcexw, sizeof(WNDCLASSEXW));
		wcexw.cbSize = sizeof(WNDCLASSEXW);
		wcexw.style = CS_HREDRAW | CS_VREDRAW;
		wcexw.lpfnWndProc = WindowProc;
		wcexw.cbClsExtra = 0;
		wcexw.cbWndExtra = 0;
		wcexw.hInstance = GetModuleHandleW(nullptr);
		wcexw.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1);
		wcexw.lpszClassName = L"TUK Framework";
		RegisterClassExW(&wcexw);
	}

	void WindowSubsystem::OnShutdown()
	{
		UnregisterClassW(wcexw.lpszClassName, wcexw.hInstance);
		ZeroMemory(&wcexw, sizeof(WNDCLASSEXW));
	}

	Window* WindowSubsystem::AddWindow(const WindowOptions& options)
	{
		DWORD style = WS_OVERLAPPEDWINDOW;
		if (options.flags & WindowFlags::Resizable)
		{
			style |= WS_THICKFRAME;
		}
		if (options.flags & WindowFlags::Fullscreen)
		{
			style |= WS_POPUP;
		}
		if (options.flags & WindowFlags::Borderless)
		{
			style &= ~WS_BORDER;
			style &= ~WS_DLGFRAME;
			style &= ~WS_THICKFRAME;
			style &= ~WS_MINIMIZEBOX;
			style &= ~WS_MAXIMIZEBOX;
			style &= ~WS_SYSMENU;
		}
		HWND hWnd = CreateWindowExW(
			0,
			wcexw.lpszClassName,
			options.title.c_str(),
			style,
			options.positionX,
			options.positionY,
			options.sizeX,
			options.sizeY,
			nullptr,
			nullptr,
			wcexw.hInstance,
			nullptr
		);
		if (!hWnd)
		{
			return nullptr;
		}
		ShowWindow(hWnd, SW_SHOW);
		UpdateWindow(hWnd);
		return windows.emplace_back(std::make_unique<WindowInternal>(hWnd)).get();
	}
}
