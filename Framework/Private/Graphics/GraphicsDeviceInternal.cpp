#include "Precompiled.hpp"
#include "Graphics/GraphicsDeviceInternal.hpp"

#include "Framework/Graphics/Buffer.hpp"
#include "Framework/Graphics/Texture.hpp"
#include "Framework/Platform/Window.hpp"

#include "../Platform/WindowInternal.hpp"

#include "BufferInternal.hpp"
#include "CommandBufferInternal.hpp"
#include "RenderTargetInternal.hpp"
#include "SwapChainInternal.hpp"
#include "TextureInternal.hpp"
#include "ShaderInternal.hpp"

#include <stdexcept>

#pragma comment(lib, "d3dcompiler.lib")

namespace
{
	Microsoft::WRL::ComPtr<ID3DBlob> CompileShader(std::string_view source,
		std::string_view entryPoint, const char* profile)
	{
		const std::string entry(entryPoint);
		UINT flags = D3DCOMPILE_ENABLE_STRICTNESS;
#ifdef _DEBUG
		flags |= D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#endif
		Microsoft::WRL::ComPtr<ID3DBlob> bytecode;
		Microsoft::WRL::ComPtr<ID3DBlob> errors;
		const HRESULT result = D3DCompile(source.data(), source.size(), "Scene shader",
			nullptr, nullptr, entry.c_str(), profile, flags, 0, &bytecode, &errors);
		if (FAILED(result))
		{
			const std::string message = errors
				? std::string(static_cast<const char*>(errors->GetBufferPointer()), errors->GetBufferSize())
				: std::format("Shader compilation failed (HRESULT: 0x{:08X}).", static_cast<unsigned long>(result));
			throw std::runtime_error(message);
		}
		return bytecode;
	}
}

namespace TUK::Framework
{
	std::unique_ptr<Shader> GraphicsDeviceInternal::CreateVertexShader(std::string_view source,
		std::string_view entryPoint) const
	{
		const auto bytecode = CompileShader(source, entryPoint, "vs_4_0");
		Microsoft::WRL::ComPtr<ID3D11VertexShader> shader;
		if (FAILED(d3dDevice->CreateVertexShader(bytecode->GetBufferPointer(), bytecode->GetBufferSize(), nullptr, &shader)))
		{
			throw std::runtime_error("Vertex shader creation failed.");
		}
		Microsoft::WRL::ComPtr<ID3D11DeviceChild> nativeShader = shader;
		return std::make_unique<ShaderInternal>(std::move(nativeShader));
	}

	std::unique_ptr<Shader> GraphicsDeviceInternal::CreatePixelShader(std::string_view source,
		std::string_view entryPoint) const
	{
		const auto bytecode = CompileShader(source, entryPoint, "ps_4_0");
		Microsoft::WRL::ComPtr<ID3D11PixelShader> shader;
		if (FAILED(d3dDevice->CreatePixelShader(bytecode->GetBufferPointer(), bytecode->GetBufferSize(), nullptr, &shader)))
		{
			throw std::runtime_error("Pixel shader creation failed.");
		}
		Microsoft::WRL::ComPtr<ID3D11DeviceChild> nativeShader = shader;
		return std::make_unique<ShaderInternal>(std::move(nativeShader));
	}

	GraphicsDeviceInternal::GraphicsDeviceInternal(Microsoft::WRL::ComPtr<ID3D11Device> d3dDevice) noexcept
		: d3dDevice(std::move(d3dDevice))
		, d3dDeviceContext(nullptr)
	{
        this->d3dDevice->GetImmediateContext(&d3dDeviceContext);
	}

	GraphicsDeviceInternal::~GraphicsDeviceInternal() noexcept
	{
		if (d3dDevice)
		{
			d3dDevice.Reset();
			d3dDevice = nullptr;
		}
	}

	ID3D11Device* GraphicsDeviceInternal::GetD3D11Device() const noexcept
    {
        assert(d3dDevice);
        return d3dDevice.Get();
	}

    ID3D11DeviceContext* GraphicsDeviceInternal::GetD3D11DeviceContext() const noexcept
    {
        assert(d3dDeviceContext);
        return d3dDeviceContext.Get();
    }

    void GraphicsDeviceInternal::Submit(const CommandBuffer& commandBuffer) const
    {
		CommandBufferInternal& commandBufferInternal = static_cast<CommandBufferInternal&>(const_cast<CommandBuffer&>(commandBuffer));
		ID3D11CommandList* d3dCommandList = commandBufferInternal.GetD3D11CommandList();
	    d3dDeviceContext->ExecuteCommandList(d3dCommandList, FALSE);
    }

	std::unique_ptr<SwapChain> GraphicsDeviceInternal::CreateSwapChain(const Window& window) const
	{
		const auto* windowInternal = dynamic_cast<const WindowInternal*>(&window);
		if (!d3dDevice || !windowInternal)
		{
			return nullptr;
		}

		const HWND hWnd = windowInternal->GetHWND();
		RECT clientRect{};
		if (!hWnd || !GetClientRect(hWnd, &clientRect)
			|| clientRect.right <= clientRect.left || clientRect.bottom <= clientRect.top)
		{
			return nullptr;
		}

		Microsoft::WRL::ComPtr<IDXGIDevice> dxgiDevice;
		if (FAILED(d3dDevice.As(&dxgiDevice)))
		{
			return nullptr;
		}

		Microsoft::WRL::ComPtr<IDXGIAdapter> adapter;
		if (FAILED(dxgiDevice->GetAdapter(&adapter)))
		{
			return nullptr;
		}

		Microsoft::WRL::ComPtr<IDXGIFactory2> factory;
		if (FAILED(adapter->GetParent(IID_PPV_ARGS(&factory))))
		{
			return nullptr;
		}

		DXGI_SWAP_CHAIN_DESC1 description{};
		description.Width = static_cast<UINT>(clientRect.right - clientRect.left);
		description.Height = static_cast<UINT>(clientRect.bottom - clientRect.top);
		description.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		description.SampleDesc.Count = 1;
		description.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		description.BufferCount = 2;
		description.Scaling = DXGI_SCALING_STRETCH;
		description.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
		description.AlphaMode = DXGI_ALPHA_MODE_IGNORE;

		Microsoft::WRL::ComPtr<IDXGISwapChain1> swapChain;
		if (FAILED(factory->CreateSwapChainForHwnd(d3dDevice.Get(), hWnd,
			&description, nullptr, nullptr, &swapChain)))
		{
			return nullptr;
		}

		if (FAILED(factory->MakeWindowAssociation(hWnd, DXGI_MWA_NO_ALT_ENTER)))
		{
			return nullptr;
		}

		Microsoft::WRL::ComPtr<IDXGISwapChain> dxgiSwapChain;
		if (FAILED(swapChain.As(&dxgiSwapChain)))
		{
			return nullptr;
		}

		Microsoft::WRL::ComPtr<ID3D11Texture2D> backBuffer;
		if (FAILED(dxgiSwapChain->GetBuffer(0, IID_PPV_ARGS(&backBuffer))))
		{
			return nullptr;
		}

		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> rtv;
		if (FAILED(d3dDevice->CreateRenderTargetView(backBuffer.Get(), nullptr, &rtv)))
		{
			return nullptr;
		}

		auto renderTarget = std::make_unique<RenderTargetInternal>(std::move(rtv));
		return std::make_unique<SwapChainInternal>(std::move(dxgiSwapChain), std::move(renderTarget));
	}

    std::unique_ptr<Buffer> GraphicsDeviceInternal::CreateBuffer(size_t size) const
	{
		D3D11_BUFFER_DESC bufferDesc{};
		bufferDesc.Usage = D3D11_USAGE_DEFAULT;
        bufferDesc.ByteWidth = static_cast<UINT>(size);
        bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

        Microsoft::WRL::ComPtr<ID3D11Buffer> buffer;
        if (FAILED(d3dDevice->CreateBuffer(
            &bufferDesc,
            nullptr,
            &buffer)))
        {
            return nullptr;
        }

        return std::make_unique<BufferInternal>(buffer);
	}

	std::unique_ptr<Texture> GraphicsDeviceInternal::CreateTexture() const
	{
		D3D11_TEXTURE2D_DESC textureDesc{};
        // TODO: 이거 어떻게 할지 생각해봐.

        Microsoft::WRL::ComPtr<ID3D11Texture2D> texture2D;
        if (FAILED(d3dDevice->CreateTexture2D(&textureDesc, nullptr, &texture2D)))
        {
            return nullptr;
        }

        return std::make_unique<TextureInternal>(texture2D);
	}

	std::unique_ptr<RenderTarget> GraphicsDeviceInternal::CreateTarget() const
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

        return std::make_unique<RenderTargetInternal>(rtv);
	}
}
