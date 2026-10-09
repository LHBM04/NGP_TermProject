#pragma once

namespace TUK::Framework
{
	class Shader
	{
	public:
		virtual ~Shader() noexcept = default;

		Shader(const Shader&) noexcept = delete;
		Shader& operator=(const Shader&) noexcept = delete;

		Shader(Shader&&) noexcept = delete;
		Shader& operator=(Shader&&) noexcept = delete;

	protected:
		Shader() noexcept = default;
	};
}
