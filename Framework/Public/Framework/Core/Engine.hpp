#pragma once

#include "EngineSubsystem.hpp"
#include "System.hpp"

namespace TUK::Framework
{
	class Game;

	class Engine : public System
	{
		friend class Game;

	public:
		Engine() noexcept;
		~Engine() noexcept override;
		
		int Run(Game& game);

		template <std::derived_from<EngineSubsystem> TSubsystem>
		TSubsystem* AddSubsystem();

		template <std::derived_from<EngineSubsystem> TSubsystem>
		[[nodiscard]] TSubsystem* GetSubsystem();

		template <std::derived_from<EngineSubsystem> TSubsystem>
		[[nodiscard]] const TSubsystem* GetSubsystem() const;

		template <std::derived_from<EngineSubsystem> TSubsystem>
		[[nodiscard]] auto GetSubsystems();

		template <std::derived_from<EngineSubsystem> TSubsystem>
		[[nodiscard]] const auto GetSubsystems() const;

		/** Overloaded for Engine */
		[[nodiscard]] static Engine* GetInstance();

	protected:
		void OnReady() override;

	private:
		void PreTick();
		void Tick();
		void PostTick();

		Game* game = nullptr;
	};

	template <std::derived_from<EngineSubsystem> TSubsystem>
	TSubsystem* Engine::AddSubsystem()
	{
		return System::AddSubsystem<TSubsystem>();
	}

	template <std::derived_from<EngineSubsystem> TSubsystem>
	TSubsystem* Engine::GetSubsystem()
	{
		return System::GetSubsystem<TSubsystem>();
	}

	template <std::derived_from<EngineSubsystem> TSubsystem>
	const TSubsystem* Engine::GetSubsystem() const
	{
		return System::GetSubsystem<TSubsystem>();
	}

	template <std::derived_from<EngineSubsystem> TSubsystem>
	auto Engine::GetSubsystems()
	{
		return System::GetSubsystems<TSubsystem>();
	}

	template <std::derived_from<EngineSubsystem> TSubsystem>
	const auto Engine::GetSubsystems() const
	{
		return System::GetSubsystems<TSubsystem>();
	}
}
