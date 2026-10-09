#pragma once

namespace TUK::Framework
{
	class Scene
	{
	public:
		virtual ~Scene() noexcept = default;

		Scene(const Scene&) = delete;
		Scene& operator=(const Scene&) = delete;

		Scene(Scene&&) = delete;
		Scene& operator=(Scene&&) = delete;

	protected:
		Scene() noexcept = default;
	};
}
