#pragma once

#include <wrl.h>
#include <dxgi1_6.h>

#include "Framework/Graphics/RenderTarget.hpp"

namespace TUK::Framework
{
	class RenderTargetInternal : public RenderTarget
	{
		friend class RenderDeviceInternal;

	public:
		RenderTargetInternal(
			Microsoft::WRL::ComPtr<ID3D11Texture2D> texture2D,
			Microsoft::WRL::ComPtr<ID3D11RenderTargetView> rtv,
			Microsoft::WRL::ComPtr<ID3D11DepthStencilView> dsv) noexcept;
		~RenderTargetInternal() noexcept override;

		RenderTargetInternal(const RenderTargetInternal&) noexcept = default;
		RenderTargetInternal& operator=(const RenderTargetInternal&) noexcept = default;
		
		RenderTargetInternal(RenderTargetInternal&&) noexcept = default;
		RenderTargetInternal& operator=(RenderTargetInternal&&) noexcept = default;

	private:
		Microsoft::WRL::ComPtr<ID3D11Texture2D> texture2D;
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> rtv;
		Microsoft::WRL::ComPtr<ID3D11DepthStencilView> dsv;
	};
}
