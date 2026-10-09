#pragma once

#include "Framework/Graphics/RenderDevice.hpp"

namespace TUK::Framework
{
	class Buffer;
	class CommandBuffer;
	class Texture;
	class RenderTarget;
	class SwapChain;

	class RenderDeviceInternal : public RenderDevice
	{
	public:
		RenderDeviceInternal(Microsoft::WRL::ComPtr<ID3D11Device> d3dDevice) noexcept;
		~RenderDeviceInternal() noexcept override;
		/** 소유권을 넘기지 않는 네이티브 객체 접근. */
		[[nodiscard]] explicit operator ID3D11Device*() const noexcept
		{
			return GetD3D11Device();
		}

		[[nodiscard]] explicit operator ID3D11DeviceContext*() const noexcept
		{
			return GetD3D11DeviceContext();
		}


		/** D3D11 Device 가져오기 */
		[[nodiscard]] ID3D11Device* GetD3D11Device() const noexcept;

		/** D3D11 Device Context 가져오기 */
		[[nodiscard]] ID3D11DeviceContext* GetD3D11DeviceContext() const noexcept;

		/** Interface Override */
		void Submit(const CommandBuffer& commandBuffer) const override;
		std::unique_ptr<SwapChain> CreateSwapChain(const Window& window) const override;
		std::unique_ptr<Buffer> CreateBuffer(size_t size) const override;
		std::unique_ptr<Texture> CreateTexture() const override;
		std::unique_ptr<RenderTarget> CreateTarget() const override;

	private:
		Microsoft::WRL::ComPtr<ID3D11Device> d3dDevice;
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> d3dDeviceContext;
	};
}
