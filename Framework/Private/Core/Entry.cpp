#include "Precompiled.hpp"

#include "Framework/Core/Engine.hpp"
#include "Framework/Core/Game.hpp"

using namespace TUK::Framework;

#ifdef _WIN32
	extern "C" INT APIENTRY wWinMain(
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
	
		std::unique_ptr<Engine> engine = std::unique_ptr<Engine>(CreateEngineInstance());
		engine->Ready();
		engine->Startup();

		if (engine->IsRunning())
		{
			std::unique_ptr<Game> game = std::unique_ptr<Game>(CreateGameInstance());
			game->Ready();
			game->Startup();

			if (!game->IsRunning())
			{
				engine->RequestQuit(game->GetQuitCode());
				return 1;
			}

			while (game->IsRunning())
			{
				engine->PreTick();
				game->PreTick();

				engine->Tick();
				game->Tick();

				engine->PostTick();
				game->PostTick();

				if (!game->IsRunning())
				{
					engine->RequestQuit(game->GetQuitCode());
				}
			}

			game->Shutdown();

			if (game->GetQuitCode() != EXIT_SUCCESS)
			{
				engine->RequestQuit(game->GetQuitCode());
			}
		}

		engine->Shutdown();
		return engine->GetQuitCode();
	}
#else
	extern "C" int main(int argc, char* argv[])
	{
		std::unique_ptr<Engine> engine = std::unique_ptr<Engine>(CreateEngineInstance());
		engine->Ready();
		engine->Startup();

		if (engine->IsRunning())
		{
			std::unique_ptr<Game> game = std::unique_ptr<Game>(CreateGameInstance());
			game->Ready();
			game->Startup();

			if (!game->IsRunning())
			{
				engine->RequestQuit(game->GetQuitCode());
				return 1;
			}

			while (game->IsRunning())
			{
				engine->PreTick();
				game->PreTick();

				engine->Tick();
				game->Tick();

				engine->PostTick();
				game->PostTick();

				if (!game->IsRunning())
				{
					engine->RequestQuit(game->GetQuitCode());
				}
			}

			game->Shutdown();

			if (game->GetQuitCode() != EXIT_SUCCESS)
			{
				engine->RequestQuit(game->GetQuitCode());
			}
		}

		engine->Shutdown();
		return engine->GetQuitCode();
	}
#endif