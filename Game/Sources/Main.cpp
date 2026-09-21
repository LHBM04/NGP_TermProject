#include "Framework/Core/Engine.h"

#include "Framework/Platform/Window.h"
#include "Framework/Platform/WindowOptions.h"
#include "Framework/Platform/WindowSubsystem.h"

using namespace TUK::Framework;

int main(int argc, char* argv[]) 
{
	Engine* engine = new Engine();
	engine->AddSubsystem<WindowSubsystem>();
	engine->Startup();

	WindowOptions options{};
	options.title = L"Virus Striker";
	options.sizeX = 1280;
	options.sizeY = 960;
	options.positionX = 100;
	options.positionY = 100;
	options.flags = WindowFlags::Resizable;
	engine->GetSubsystem<WindowSubsystem>()->AddWindow(options);

	while (true)
	{
		
	}
	
	engine->Shutdown();
	delete engine;
}