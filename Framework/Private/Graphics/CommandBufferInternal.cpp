#include "Precompiled.hpp"
#include "CommandBufferInternal.hpp"

#include "Framework/Graphics/ScissorRect.hpp"
#include "Framework/Graphics/Shader.hpp"
#include "Framework/Graphics/Viewport.hpp"

#include "BufferInternal.hpp"
#include "ShaderInternal.hpp"
#include "RenderTargetInternal.hpp"

#include <stdexcept>

namespace TUK::Framework
{
	CommandBufferInternal::CommandBufferInternal(Microsoft::WRL::ComPtr<ID3D11DeviceContext> d3dDeviceContext) noexcept
		: d3dDeviceContext(d3dDeviceContext)
		, d3dCommandList(nullptr)
	{
	}

	CommandBufferInternal::~CommandBufferInternal() noexcept
	{
		if (d3dCommandList)
		{
			d3dCommandList.Reset();
			d3dCommandList = nullptr;
		}
	}

	ID3D11DeviceContext* CommandBufferInternal::GetD3D11DeviceContext() const noexcept
	{
		assert(d3dDeviceContext);
		return d3dDeviceContext.Get();
	}

	ID3D11CommandList* CommandBufferInternal::GetD3D11CommandList() const noexcept
	{
		assert(d3dCommandList);
		return d3dCommandList.Get();
	}

	void CommandBufferInternal::Begin()
	{
		assert(d3dDeviceContext);
	}
	
	void CommandBufferInternal::End()
	{
		assert(d3dDeviceContext);
		const HRESULT result = d3dDeviceContext->FinishCommandList(FALSE,
			d3dCommandList.ReleaseAndGetAddressOf());
		if (FAILED(result))
		{
			throw std::runtime_error(std::format("명령 리스트 생성 실패 (HRESULT: 0x{:08X}).",
				static_cast<unsigned long>(result)));
		}
	}

	void CommandBufferInternal::SetTarget(RenderTarget& target)
	{
		assert(d3dDeviceContext);

		RenderTargetInternal* targetInternal = static_cast<RenderTargetInternal*>(&target);
		ID3D11RenderTargetView* d3dRtv = targetInternal->GetD3D11RenderTargetView();

		d3dDeviceContext->OMSetRenderTargets(1, &d3dRtv, nullptr);
	}

	void CommandBufferInternal::SetTargets(std::span<RenderTarget* const> targets)
	{
		assert(d3dDeviceContext);
		assert(targets.size() <= D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT);

		std::array<ID3D11RenderTargetView*, D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT> rtvs{};

		for (size_t i = 0; i < targets.size(); ++i)
		{
			assert(targets[i]);

			auto& internal = static_cast<RenderTargetInternal&>(*targets[i]);
			rtvs[i] = internal.GetD3D11RenderTargetView();
		}

		d3dDeviceContext->OMSetRenderTargets(static_cast<UINT>(targets.size()), rtvs.data(), nullptr);
	}

	void CommandBufferInternal::ClearTarget(RenderTarget& target, const ColorRGBA<float>& color) const
	{
		assert(d3dDeviceContext);

		RenderTargetInternal& targetInternal = static_cast<RenderTargetInternal&>(target);
		ID3D11RenderTargetView* d3dRtv = targetInternal.GetD3D11RenderTargetView();

		const FLOAT colors[4]{ color.GetR(), color.GetG(), color.GetB(), color.GetA() };
		d3dDeviceContext->ClearRenderTargetView(d3dRtv, colors);
	}

	void CommandBufferInternal::SetVertexShader(const Shader& vertexShader)
	{
		assert(d3dDeviceContext);
		ShaderInternal& shaderInternal = static_cast<ShaderInternal&>(const_cast<Shader&>(vertexShader));
		d3dDeviceContext->VSSetShader(shaderInternal.GetD3D11Shader<ID3D11VertexShader>(), nullptr, 0);
	}

	void CommandBufferInternal::SetPixelShader(const Shader& pixelShader)
	{
		assert(d3dDeviceContext);
		ShaderInternal& shaderInternal = static_cast<ShaderInternal&>(const_cast<Shader&>(pixelShader));
		d3dDeviceContext->PSSetShader(shaderInternal.GetD3D11Shader<ID3D11PixelShader>(), nullptr, 0);
	}

	void CommandBufferInternal::SetVertexBuffer(
		Buffer& buffer,
		unsigned int stride,
		unsigned int offset,
		unsigned int instanceOffset)
	{
		assert(d3dDeviceContext);
		
		BufferInternal& buffeInternal = static_cast<BufferInternal&>(buffer);
		ID3D11Buffer* d3dBuffer = buffeInternal.GetD3D11Buffer();
		d3dDeviceContext->IASetVertexBuffers(instanceOffset, 1, &d3dBuffer, &stride, &offset);
	}

	void CommandBufferInternal::SetIndexBuffer(
		Buffer& buffer, 
		IndexFormat format, 
		unsigned int offset)
	{
		assert(d3dDeviceContext);

		BufferInternal& bufferInternal = static_cast<BufferInternal&>(buffer);
		d3dDeviceContext->IASetIndexBuffer(bufferInternal.GetD3D11Buffer(), DXGI_FORMAT_R32G32_SINT, offset);
	}

	void CommandBufferInternal::SetViewport(const Viewport& viewport)
	{
		assert(d3dDeviceContext);

		D3D11_VIEWPORT viewPort{};
		viewPort.Width = static_cast<FLOAT>(viewport.width);
		viewPort.Height = static_cast<FLOAT>(viewport.height);
		viewPort.TopLeftX = static_cast<FLOAT>(viewport.x);
		viewPort.TopLeftY = static_cast<FLOAT>(viewport.y);
		viewPort.MinDepth = static_cast<FLOAT>(viewport.min);
		viewPort.MaxDepth = static_cast<FLOAT>(viewport.max);
		d3dDeviceContext->RSSetViewports(1, &viewPort);
	}

	void CommandBufferInternal::SetScissorRect(const ScissorRect& rect)
	{
		assert(d3dDeviceContext);

		D3D11_RECT scissorRect{};
		scissorRect.left = static_cast<LONG>(rect.left);
		scissorRect.top = static_cast<LONG>(rect.top);
		scissorRect.right = static_cast<LONG>(rect.right);
		scissorRect.bottom = static_cast<LONG>(rect.bottom);
		d3dDeviceContext->RSSetScissorRects(1, &scissorRect);
	}

	void CommandBufferInternal::Draw(
		unsigned int vertexCount, 
		unsigned int instanceCount, 
		unsigned int startVertex,
		unsigned int startInstance)
	{
		assert(d3dDeviceContext);
		d3dDeviceContext->DrawInstanced(vertexCount, instanceCount, startVertex, startInstance);
	}

	void CommandBufferInternal::DrawIndexed(
		unsigned int indexCount, 
		unsigned int instanceCount,
		unsigned int startIndex, 
		int vertexOffset, 
		unsigned int startInstance)
	{
		assert(d3dDeviceContext);
		d3dDeviceContext->DrawIndexedInstanced(indexCount, instanceCount, startIndex, vertexOffset, startInstance);
	}

	void CommandBufferInternal::Transition(Texture& texture, ResourceState state)
	{
		assert(d3dDeviceContext);
	}
}
