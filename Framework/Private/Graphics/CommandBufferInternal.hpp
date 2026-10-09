#pragma once

#include <d3d11_4.h>

#include <wrl.h>

#include "Framework/Graphics/CommandBuffer.hpp"

namespace TUK::Framework
{
	class CommandBufferInternal : public CommandBuffer
	{
	public:
		CommandBufferInternal(Microsoft::WRL::ComPtr<ID3D11DeviceContext> d3dDeviceContext) noexcept;
		~CommandBufferInternal() noexcept override;
		/** 소유권을 넘기지 않는 네이티브 객체 접근. */
		[[nodiscard]] explicit operator ID3D11DeviceContext*() const noexcept
		{
			return GetD3D11DeviceContext();
		}

		[[nodiscard]] explicit operator ID3D11CommandList*() const noexcept
		{
			return GetD3D11CommandList();
		}


		[[nodiscard]] ID3D11DeviceContext* GetD3D11DeviceContext() const noexcept;
		[[nodiscard]] ID3D11CommandList* GetD3D11CommandList() const noexcept;

		void Begin() override;
		void End() override;

		void SetTarget(RenderTarget& target) override;
		void SetTargets(std::span<RenderTarget* const> targets) override;

		void ClearTarget(RenderTarget& target, const ColorRGBA<float>& color) const override;

		void SetVertexShader(const Shader& vertexShader) override;
		void SetPixelShader(const Shader& pixelShader) override;

		void SetVertexBuffer(
			Buffer& buffer,
			unsigned int stride,
			unsigned int offset = 0,
			unsigned int instanceOffset = 0) override;
		void SetIndexBuffer(
			Buffer& buffer, 
			IndexFormat format, 
			unsigned int offset = 0) override;

		void SetViewport(const Viewport& viewport) override;
		void SetScissorRect(const ScissorRect& rect) override;

		void Draw(
			unsigned int vertexCount, 
			unsigned int instanceCount, 
			unsigned int startVertex, 
			unsigned int startInstance) override;
		void DrawIndexed(
			unsigned int indexCount, 
			unsigned int instanceCount, 
			unsigned int startIndex, 
			int vertexOffset, 
			unsigned int startInstance) override;

		void Transition(Texture& texture, ResourceState state) override;

	private:
		/** D3D11 디바이스 컨텍스트 */
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> d3dDeviceContext;

		/** D3D11 명령 리스트 */
		Microsoft::WRL::ComPtr<ID3D11CommandList> d3dCommandList;
	};
}
