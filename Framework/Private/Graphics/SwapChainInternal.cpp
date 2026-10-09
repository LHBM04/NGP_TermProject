#include "Precompiled.hpp"
#include "Graphics/SwapChainInternal.hpp"

#include "Framework/Graphics/CommandBuffer.hpp"
#include "Framework/Graphics/RenderTarget.hpp"

#include "RenderTargetInternal.hpp"

#include <stdexcept>

namespace TUK::Framework
{
	SwapChainInternal::SwapChainInternal(Microsoft::WRL::ComPtr<IDXGISwapChain> dxgiSwapChain,
		std::unique_ptr<RenderTargetInternal> renderTarget) noexcept
		: dxgiSwapChain(std::move(dxgiSwapChain))
		, renderTarget(std::move(renderTarget))
	{
		assert(this->dxgiSwapChain && this->renderTarget);
	}

	SwapChainInternal::~SwapChainInternal() noexcept
	{
		// 멤버는 선언의 역순으로 파괴되어 RTV가 스왑 체인보다 먼저 해제된다.
	}

	Microsoft::WRL::ComPtr<IDXGISwapChain> SwapChainInternal::GetDXGISwapChain() const noexcept
	{
		assert(dxgiSwapChain);
		return dxgiSwapChain;
	}

	RenderTarget& SwapChainInternal::GetTarget() const noexcept
	{
		assert(renderTarget);
		return *renderTarget;
	}

	void SwapChainInternal::Clear(CommandBuffer& commandBuffer) const
	{
		commandBuffer.ClearTarget(GetTarget(), ColorRGBA<float>(0.0f, 0.0f, 0.0f, 1.0f));
	}

	void SwapChainInternal::Present() const
	{
		const HRESULT result = dxgiSwapChain->Present(1, 0);
		if (FAILED(result))
		{
			throw std::runtime_error(std::format("스왑 체인 표시 실패 (HRESULT: 0x{:08X}).",
				static_cast<unsigned long>(result)));
		}
	}
}
