#pragma once

namespace TUK::Framework
{
	class Buffer
	{
	public:
		Buffer() noexcept = default;
		virtual ~Buffer() noexcept = default;

		Buffer(const Buffer&) noexcept = delete;
		Buffer& operator=(const Buffer&) noexcept = delete;

		Buffer(Buffer&&) noexcept = delete;
		Buffer& operator=(Buffer&&) noexcept = delete;
	};
}
