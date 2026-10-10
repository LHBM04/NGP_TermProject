#pragma once

#include "Framework/Core/Game.hpp"

#include "Framework/Platform/Window.hpp"

namespace TUK::Game
{
	class MyGame final : public Framework::Game
	{
		DECLARE_GAME_INSTANCE();

	public:
		void Ready() override;

	private:
		MyGame() noexcept;
		~MyGame() noexcept override;

		void RequireWindow();
		void RequireScenes();

		Window* window;
	};
}
