#pragma once

namespace TUK::Framework
{
	class Texture
	{
	public:
		virtual ~Texture() noexcept = default;

		Texture(const Texture&) noexcept = delete;
		Texture& operator=(const Texture&) noexcept = delete;

		Texture(Texture&&) noexcept = delete;
		Texture& operator=(Texture&&) noexcept = delete;

	protected:
		Texture() noexcept = default;
	};
}
