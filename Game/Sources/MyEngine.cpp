#include "Precompiled.hpp"
#include "MyEngine.hpp"

DEFINE_ENGINE_INSTANCE(::TUK::Game::MyEngine)

namespace TUK::Game
{
	void MyEngine::Ready()
	{
		AddSubsystem<Framework::TimeSubsystem>();
		AddSubsystem<Framework::WindowSubsystem>();
		AddSubsystem<Framework::EventSubsystem>();
		AddSubsystem<Framework::RenderSubsystem>();
	}
}
