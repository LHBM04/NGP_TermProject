#pragma once

namespace TUK::Framework
{
	class Sampler
	{
	public:
		virtual ~Sampler() noexcept = default;

		Sampler(const Sampler&) noexcept = delete;
		Sampler& operator=(const Sampler&) noexcept = delete;

		Sampler(Sampler&&) noexcept = delete;
		Sampler& operator=(Sampler&&) noexcept = delete;

	protected:
		Sampler() noexcept = default;
	};
}
