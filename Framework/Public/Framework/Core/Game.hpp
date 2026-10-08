#pragma once

#include <concepts>

#include "GameSubsystem.hpp"
#include "System.hpp"
#include "../Platform/WindowOptions.hpp"

namespace TUK::Framework
{
	class TimeSubsystem;

	class Game : public System
	{
		friend class Engine;

	public:
		explicit Game(const WindowOptions& windowOptions = WindowOptions{});
		~Game() override;

		template <std::derived_from<GameSubsystem> TSubsystem>
		TSubsystem* AddSubsystem();

		template <std::derived_from<GameSubsystem> TSubsystem>
		[[nodiscard]] TSubsystem* GetSubsystem();

		template <std::derived_from<GameSubsystem> TSubsystem>
		[[nodiscard]] const TSubsystem* GetSubsystem() const;

		[[nodiscard]] auto GetSubsystems();
		[[nodiscard]] const auto GetSubsystems() const;

		/** Overloaded for Game */
		[[nodiscard]] static Game* GetInstance();

	protected:
		void OnReady() override;
		void SetWindowOptions(const WindowOptions& windowOptions);

	private:
		void Startup();
		void Tick();
		WindowOptions windowOptions;
	};

	template <std::derived_from<GameSubsystem> TSubsystem>
	TSubsystem* Game::AddSubsystem()
	{
		return System::AddSubsystem<TSubsystem>();
	}

	template <std::derived_from<GameSubsystem> TSubsystem>
	TSubsystem* Game::GetSubsystem()
	{
		return System::GetSubsystem<TSubsystem>();
	}

	template <std::derived_from<GameSubsystem> TSubsystem>
	const TSubsystem* Game::GetSubsystem() const
	{
		return System::GetSubsystem<TSubsystem>();
	}

	inline auto Game::GetSubsystems()
	{
		return System::GetSubsystems<GameSubsystem>();
	}

	inline const auto Game::GetSubsystems() const
	{
		return System::GetSubsystems<GameSubsystem>();
	}
}
