#pragma once

namespace TUK::Framework
{
	class Entity
	{
	public:
		virtual ~Entity() noexcept;

		Entity(const Entity&) = delete;
		Entity& operator=(const Entity&) = delete;

		Entity(Entity&&) noexcept = delete;
		Entity& operator=(Entity&&) noexcept = delete;

	protected:
		Entity() noexcept;
	};
}
