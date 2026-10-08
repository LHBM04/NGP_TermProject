#include "Precompiled.hpp"
#include "Framework/Core/System.hpp"

namespace TUK::Framework
{
	System::System() noexcept
		: isRunning(false)
		, quitCode(EXIT_SUCCESS)
		, options()
		, subsystems()
		, subsystemsByType()
	{
	}

	System::~System() noexcept
	{
		isRunning = false;
		subsystemsByType.clear();
		subsystems.clear();
	}

	void System::RequestQuit(int code) noexcept
	{
		if (quitCode == EXIT_SUCCESS)
		{
			quitCode = code;
		}

		isRunning = false;
	}

	void System::ReportError(std::string_view message)
	{
		const auto line = std::format("{}\n", message);
		OutputDebugStringA(line.c_str());
		RequestQuit(EXIT_FAILURE);
	}

	bool System::IsRunning() const noexcept
	{
		return isRunning;
	}

	void System::Ready()
	{
		if (isReady) return;
		OnReady();
		isReady = true;
	}

	void System::OnReady()
	{
	}

	void System::Startup()
	{
		// 게임 서비스 시작이 이미 실행 중인 엔진의 싱글턴을 덮어쓰지 않도록 한다.
		if (!instance) instance = this;
		Ready();
		if (quitCode != EXIT_SUCCESS) return;

		isRunning = true;

		std::ranges::sort(subsystems, std::ranges::less{}, &Subsystem::GetPriority);
		for (std::unique_ptr<Subsystem>& subsystem : subsystems)
		{
			subsystem->OnStartup();
		}
	}

	void System::Shutdown()
	{
		isRunning = false;

		for (std::unique_ptr<Subsystem>& subsystem : subsystems | std::views::reverse)
		{
			subsystem->OnShutdown();
		}

		subsystems.clear();
		subsystemsByType.clear();

		isReady = false;
		if (instance == this) instance = nullptr;
	}

	int System::GetQuitCode() const noexcept
	{
		return quitCode;
	}

	System* System::GetInstance()
	{
		assert(instance);
		return instance;
	}

	System* System::instance = nullptr;
}
