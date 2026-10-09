#include "Precompiled.hpp"
#include "MyEngine.hpp"

namespace TUK::Game
{
	MyEngine::MyEngine() noexcept
	{
	}

	MyEngine::~MyEngine() noexcept
	{
	}

	void MyEngine::OnReady()
	{
		AddSubsystem<Framework::TimeSubsystem>();
		AddSubsystem<Framework::WindowSubsystem>();
		AddSubsystem<Framework::EventSubsystem>();
		AddSubsystem<Framework::RenderSubsystem>();
	}
}
