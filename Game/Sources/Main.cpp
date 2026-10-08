#include "Precompiled.hpp"

using namespace TUK;

INT APIENTRY wWinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPTSTR lpCmdLine, 
	_In_ INT nCmdShow)
{
#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	AllocConsole();
	FILE* consoleStream = nullptr;
	freopen_s(&consoleStream, "CONOUT$", "w", stdout);
	freopen_s(&consoleStream, "CONOUT$", "w", stderr);
#endif

	Framework::Vector2D vec(1, 1);
	std::cout << "Vector2D: (" << vec.GetX() << ", " << vec.GetY() << ")" << std::endl;
	while (true);

	return 0;
}