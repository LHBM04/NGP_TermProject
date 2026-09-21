#pragma once

#include <vector>
#include <memory>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include "Framework/Core/Subsystem.h"

namespace TUK::Framework
{
	struct WindowOptions;
	class Window;

	class WindowSubsystem : public Subsystem
	{
	public:
		void OnStartup() override;
		void OnShutdown() override;

		Window* AddWindow(const WindowOptions& options);

	private:
		WNDCLASSEXW wcexw;
		std::vector<std::unique_ptr<Window>> windows;
	};
}
