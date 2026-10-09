#pragma once

#include "Framework/Core/Engine.hpp"

namespace TUK::Game
{
	class MyEngine final : public Framework::Engine
	{
		DECLARE_ENGINE_INSTANCE();

	public:
		void Ready() override;

	private:
		MyEngine() noexcept = default;
		~MyEngine() noexcept override = default;
	};
}
