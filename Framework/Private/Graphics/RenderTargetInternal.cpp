#include "Precompiled.hpp"
#include "Graphics/RenderTargetInternal.hpp"

namespace TUK::Framework
{
	RenderTargetInternal::RenderTargetInternal(
		Microsoft::WRL::ComPtr<ID3D11Texture2D> texture2D,
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> rtv,
		Microsoft::WRL::ComPtr<ID3D11DepthStencilView> dsv) noexcept
		: texture2D(texture2D)
		, rtv(rtv)
		, dsv(dsv)
	{
	}

	RenderTargetInternal::~RenderTargetInternal() noexcept
	{
		if (texture2D)
		{
			texture2D.Reset(); 
			texture2D = nullptr;
		}

		if (rtv)
		{
			rtv.Reset(); 
			rtv = nullptr;
		}

		if (dsv)
		{
			dsv.Reset(); 
			dsv = nullptr;
		}
	}


}
