#pragma once

#include <unordered_map>
#include <memory>
#include <vector>
#include <typeindex>

namespace TUK::Framework
{
	class Subsystem;

	class Engine
	{
	public:
		Engine() = default;
		~Engine() = default;

		Engine(const Engine&) = delete;
		Engine& operator=(const Engine&) = delete;

		Engine(Engine&&) = default;
		Engine& operator=(Engine&&) = default;

		void Startup();
		void Shutdown();

		/** Singleton ∆–≈œ */
		[[nodiscard]] static Engine& GetInstance();

		template <class TSubsystem>
		[[nodiscard]] TSubsystem* GetSubsystem();

		template <class TSubsystem>
		[[nodiscard]] const TSubsystem* GetSubsystem() const;

	private:
		static Engine* instance;

		std::unordered_map<std::type_index, std::unique_ptr<Subsystem>> subsystems;
		std::vector<Subsystem*> subsystemsByType;
	};

	template <class TSubsystem>
	TSubsystem* Engine::GetSubsystem()
	{
		auto it = subsystems.find(typeid(TSubsystem));
		if (it != subsystems.end())
		{
			return static_cast<TSubsystem*>(it->second.get());
		}
		return nullptr;
	}

	template <class TSubsystem>
	const TSubsystem* Engine::GetSubsystem() const
	{
		auto it = subsystems.find(typeid(TSubsystem));
		if (it != subsystems.end())
		{
			return static_cast<const TSubsystem*>(it->second.get());
		}
		return nullptr;
	}
}
