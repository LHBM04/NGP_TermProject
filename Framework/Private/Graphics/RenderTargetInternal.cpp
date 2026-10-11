#include "Precompiled.hpp"
#include "Graphics/RenderTargetInternal.hpp"

namespace TUK::Framework
{
	namespace
	{
		D3D11_TEXTURE2D_DESC GetTextureDescription(ID3D11RenderTargetView* view) noexcept
		{
			Microsoft::WRL::ComPtr<ID3D11Resource> resource;
			view->GetResource(&resource);
			Microsoft::WRL::ComPtr<ID3D11Texture2D> texture;
			D3D11_TEXTURE2D_DESC description{};
			if (SUCCEEDED(resource.As(&texture)))
			{
				texture->GetDesc(&description);
			}
			return description;
		}
	}

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
		return static_cast<int>(GetTextureDescription(rtv.Get()).Width);
	}

	int RenderTargetInternal::GetHeight() const noexcept
	{
		return static_cast<int>(GetTextureDescription(rtv.Get()).Height);
	}

	TextureFormat RenderTargetInternal::GetFormat() const noexcept
	{
		// 현재 CreateTarget/CreateSwapChain은 모두 RGBA8 타깃을 생성한다.
		assert(GetTextureDescription(rtv.Get()).Format == DXGI_FORMAT_R8G8B8A8_UNORM);
		return TextureFormat::RGBA8;
	}
}
