#include "Precompiled.hpp"
#include "MyEngine.hpp"
#include "MyGame.hpp"

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

	TUK::Game::MyEngine engine;
	TUK::Game::MyGame game;

	return engine.Run(game);
}