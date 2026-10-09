#include "Precompiled.hpp"
#include "Framework/Graphics/RenderSubsystem.hpp"

#include "Framework/Core/Engine.hpp"

#include "Framework/Graphics/CommandBuffer.hpp"
#include "Framework/Graphics/RenderDevice.hpp"
#include "Framework/Graphics/SwapChain.hpp"

#include "Platform/WindowInternal.hpp"

#include "CommandBufferInternal.hpp"
#include "RenderDeviceInternal.hpp"
#include "SwapChainInternal.hpp"

namespace TUK::Framework
{
	RenderSubsystem::RenderSubsystem() noexcept
		: EngineSubsystem(30)
	{	
	}

	RenderSubsystem::~RenderSubsystem() noexcept
	{
		if (device)
		{
			device.reset();
			device = nullptr;
		}
	}

	void RenderSubsystem::RegisterWindow(const Window& window)
	{
		if (swapChains.contains(&window))
		{
			return;
		}

		std::unique_ptr<SwapChain> swapChain = device->CreateSwapChain(window);
		if (!swapChain)
		{
			Engine::GetInstance()->ReportError("창의 스왑 체인 생성에 실패했습니다.");
			return;
		}

		swapChains.try_emplace(&window, std::move(swapChain));
	}

	void RenderSubsystem::UnregisterWindow(const Window& window)
	{
		swapChains.erase(&window);
	}

	RenderDevice* RenderSubsystem::GetDevice() const noexcept
	{
		assert(device);
		return device.get();
	}

	CommandBuffer* RenderSubsystem::GetCommandBuffer() const noexcept
	{
		assert(commandBuffer);
		return commandBuffer.get();
	}
	
	void RenderSubsystem::OnStartup()
	{
		// TODO: 구체화 반드시 할 것.
		Microsoft::WRL::ComPtr<ID3D11Device> d3dDevice;
		D3D_FEATURE_LEVEL featureLevel = D3D_FEATURE_LEVEL_11_0;

		if (FAILED(D3D11CreateDevice(
			nullptr,
			D3D_DRIVER_TYPE_HARDWARE,
			nullptr,
			0,
			nullptr,
			0,
			D3D11_SDK_VERSION,
			&d3dDevice,
			&featureLevel,
			nullptr)))
		{
			// 실패했으니까 프로그램 종료되어야 함.
			Engine::GetInstance()->RequestQuit(1);
			return;
		}

		device = std::make_unique<RenderDeviceInternal>(d3dDevice);

		Microsoft::WRL::ComPtr<ID3D11DeviceContext> d3dDeviceContext;
		if (FAILED(d3dDevice->CreateDeferredContext(0, &d3dDeviceContext)))
		{
			// 실패했으니까 프로그램 종료되어야 함.
			Engine::GetInstance()->RequestQuit(1);
			return;
		}

		commandBuffer = std::make_unique<CommandBufferInternal>(d3dDeviceContext);
	}

	void RenderSubsystem::OnShutdown()
	{
		commandBuffer.reset();
		swapChains.clear();
		if (device)
		{
			device.reset();
			device = nullptr;
		}
	}

	void RenderSubsystem::PreTick()
	{
		commandBuffer->Begin();

		for (const auto& entry : swapChains)
		{
			entry.second->Clear(*commandBuffer);
		}
	}

	void RenderSubsystem::PostTick()
	{
		commandBuffer->End();
		device->Submit(*commandBuffer);
		for (const auto& entry : swapChains)
		{
			entry.second->Present();
		}
	}
}
