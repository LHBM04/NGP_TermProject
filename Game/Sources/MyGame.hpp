#pragma once

#include "Framework/Core/Game.hpp"

namespace TUK::Game
{
	class MyGame final : public Framework::Game
	{
	public:
		MyGame() noexcept;
		~MyGame() noexcept override;

		void OnReady() override;
	};
}
