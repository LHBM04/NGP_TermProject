#pragma once

#include <concepts>

#include "GameSubsystem.hpp"
#include "System.hpp"

#define DECLARE_GAME_INSTANCE() \
	friend ::TUK::Framework::Game* ::TUK::Framework::CreateGameInstance()

#define DEFINE_GAME_INSTANCE(GameType) \
	namespace TUK::Framework \
	{ \
		Game* CreateGameInstance() \
		{ \
			static_assert(std::derived_from<GameType, Game>); \
			return new GameType(); \
		} \
	}

namespace TUK::Framework
{
	class Game;
	extern Game* CreateGameInstance();

	class Game : public System
	{
		friend class Engine;

	public:
		~Game() noexcept override = default;

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

		void Tick() override;

	protected:
		Game() noexcept = default;
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
