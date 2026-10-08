#pragma once

#include "Framework/Graphics/RenderDevice.hpp"

namespace TUK::Framework
{
	class RenderDeviceInternal : public RenderDevice
	{
	public:
		RenderDeviceInternal() noexcept;
		~RenderDeviceInternal() noexcept;

		RenderDeviceInternal(const RenderDeviceInternal&) noexcept;
		RenderDeviceInternal& operator=(const RenderDeviceInternal&) noexcept;
		
		RenderDeviceInternal(RenderDeviceInternal&&) noexcept;
		RenderDeviceInternal& operator=(RenderDeviceInternal&&) noexcept;
		
		/** D3D11 Device °¡Á®¿À±â */
		[[nodiscard]] ID3D11Device& GetD3D11Device() const noexcept;

		/** ·»´õ Å¸°Ù »ý¼º */
		[[nodiscard]] RenderTarget* CreateRenderTarget() const override;

	private:
		Microsoft::WRL::ComPtr<ID3D11Device> d3dDevice;
	};
}
