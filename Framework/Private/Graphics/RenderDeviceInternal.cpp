#include "Precompiled.hpp"
#include "Graphics/RenderDeviceInternal.hpp"

#include "RenderTargetInternal.hpp"

namespace TUK::Framework
{
	RenderDeviceInternal::RenderDeviceInternal() noexcept
	{
	}

	RenderDeviceInternal::~RenderDeviceInternal() noexcept
	{
	}

	RenderDeviceInternal::RenderDeviceInternal(const RenderDeviceInternal&) noexcept
	{
	}

	ID3D11Device& RenderDeviceInternal::GetD3D11Device() const noexcept
    {
        assert(d3dDevice);
        return *d3dDevice.Get();
	}

	RenderTarget* RenderDeviceInternal::CreateRenderTarget() const
	{
        assert(d3dDevice);

		D3D11_TEXTURE2D_DESC textureDesc{};
        textureDesc.Width = 1280;
        textureDesc.Height = 960;
        textureDesc.MipLevels = 1;
        textureDesc.ArraySize = 1;
        textureDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        textureDesc.SampleDesc.Count = 1;
        textureDesc.Usage = D3D11_USAGE_DEFAULT;
        textureDesc.BindFlags = D3D11_BIND_RENDER_TARGET;

		Microsoft::WRL::ComPtr<ID3D11Texture2D> texture2D;
        if (FAILED(d3dDevice->CreateTexture2D(&textureDesc, nullptr, &texture2D)))
        {
            return nullptr;
        }

        Microsoft::WRL::ComPtr<ID3D11RenderTargetView> rtv;
        if (FAILED(d3dDevice->CreateRenderTargetView(texture2D.Get(), nullptr, &rtv)))
        {
            if (texture2D)
            {    
               texture2D.Reset();
			   texture2D = nullptr;
			}

            return nullptr;
        }

        Microsoft::WRL::ComPtr<ID3D11DepthStencilView> dsv;
        if (FAILED(d3dDevice->CreateDepthStencilView(texture2D.Get(), nullptr, &dsv)))
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

            return nullptr;
        }

		return new RenderTargetInternal(texture2D, rtv, dsv);
	}
}
