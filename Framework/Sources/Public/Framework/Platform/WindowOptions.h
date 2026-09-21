#pragma once

#include <string>

#include "Framework/Platform/WindowFlags.h"

namespace TUK::Framework
{
	struct WindowOptions
	{
		std::wstring title = L"TUK Framework";
		int sizeX = 800;
		int sizeY = 600;
		int positionX = 100;
		int positionY = 100;
		int flags = WindowFlags::None;
	};
}
