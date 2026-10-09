#include "Precompiled.hpp"
#include "Graphics/RenderTargetInternal.hpp"

namespace TUK::Framework
{
	RenderTargetInternal::RenderTargetInternal(Microsoft::WRL::ComPtr<ID3D11RenderTargetView> rtv) noexcept
		: rtv(rtv)
	{
	}

	RenderTargetInternal::~RenderTargetInternal() noexcept
	{
		if (rtv)
		{
			rtv.Reset(); 
			rtv = nullptr;
		}
	}

	ID3D11RenderTargetView* RenderTargetInternal::GetD3D11RenderTargetView() const noexcept
	{
		assert(rtv);
		return rtv.Get();
	}

	int RenderTargetInternal::GetWidth() const noexcept
	{
		return 0;
	}

	int RenderTargetInternal::GetHeight() const noexcept
	{
		return 0;
	}

	TextureFormat RenderTargetInternal::GetFormat() const noexcept
	{
		return TextureFormat::R8;
	}
}
