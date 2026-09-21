#pragma once

namespace TUK::Framework
{
	class Subsystem
	{
	public:
		Subsystem() = default;
		virtual ~Subsystem() = default;

		Subsystem(const Subsystem&) = delete;
		Subsystem& operator=(const Subsystem&) = delete;
		
		Subsystem(Subsystem&&) = default;
		Subsystem& operator=(Subsystem&&) = default;

		virtual void OnStartup() = 0;
		virtual void OnShutdown() = 0;
	};
}
