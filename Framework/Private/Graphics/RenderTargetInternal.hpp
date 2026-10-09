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
		RenderTargetInternal(Microsoft::WRL::ComPtr<ID3D11RenderTargetView> rtv) noexcept;
		~RenderTargetInternal() noexcept override;
		/** 소유권을 넘기지 않는 네이티브 객체 접근. */
		[[nodiscard]] explicit operator ID3D11RenderTargetView*() const noexcept
		{
			return GetD3D11RenderTargetView();
		}


		RenderTargetInternal(const RenderTargetInternal&) noexcept = default;
		RenderTargetInternal& operator=(const RenderTargetInternal&) noexcept = default;
		
		RenderTargetInternal(RenderTargetInternal&&) noexcept = delete;
		RenderTargetInternal& operator=(RenderTargetInternal&&) noexcept = delete;

		[[nodiscard]] ID3D11RenderTargetView* GetD3D11RenderTargetView() const noexcept;

		/** Interface Override */
		[[nodiscard]] int GetWidth() const noexcept override;
		[[nodiscard]] int GetHeight() const noexcept override;
		[[nodiscard]] TextureFormat GetFormat() const noexcept override;

	private:
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> rtv;
	};
}
