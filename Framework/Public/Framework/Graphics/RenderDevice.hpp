#pragma once 

namespace TUK::Framework
{
	class RenderTarget;

	class RenderDevice
	{
	public:
		RenderDevice() noexcept;
		~RenderDevice() noexcept;

		RenderDevice(const RenderDevice&) noexcept;
		RenderDevice& operator=(const RenderDevice&) noexcept;
		
		RenderDevice(RenderDevice&&) noexcept;
		RenderDevice& operator=(RenderDevice&&) noexcept;

		virtual bool Initialize() = 0;
		virtual void Release() noexcept = 0;

		[[nodiscard]] virtual RenderTarget* CreateRenderTarget() const = 0;
	};
}
