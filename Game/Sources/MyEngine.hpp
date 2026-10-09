#pragma once

#include "Framework/Core/Engine.hpp"

namespace TUK::Game
{
	class MyEngine final : public Framework::Engine
	{
	public:
		MyEngine() noexcept;
		~MyEngine() noexcept override;

		void OnReady() override;
	};
}
