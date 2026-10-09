#pragma once

#include <span>

#include "ResourceState.hpp"
#include "../Math/ColorRGBA.hpp"

namespace TUK::Framework
{
	struct ScissorRect;
	struct Viewport;

	class RenderTarget;
	class Buffer;
	class Texture;
	class Shader;

	enum class IndexFormat : unsigned char
	{
		Undefined,
		UInt16,
		UInt32
	};

	class CommandBuffer
	{
	public:
		virtual ~CommandBuffer() noexcept = default;

		CommandBuffer(const CommandBuffer&) noexcept;
		CommandBuffer& operator=(const CommandBuffer&) noexcept;

		CommandBuffer(CommandBuffer&&) noexcept;
		CommandBuffer& operator=(CommandBuffer&&) noexcept;

		virtual void Begin() = 0;
		virtual void End() = 0;

		virtual void SetTarget(RenderTarget& target) = 0;
		virtual void SetTargets(std::span<RenderTarget* const> targets) = 0;

		virtual void ClearTarget(RenderTarget& target, const ColorRGBA<float>& color)  const = 0;
		
		virtual void SetVertexShader(const Shader& vertexShader) = 0;
		virtual void SetPixelShader(const Shader& pixelShader) = 0;

		virtual void SetVertexBuffer(
			Buffer& buffer, 
			unsigned int stride, 
			unsigned int offset = 0, 
			unsigned int instanceOffset = 0) = 0;
		virtual void SetIndexBuffer(
			Buffer& buffer, 
			IndexFormat format, 
			unsigned int offset = 0) = 0;

		virtual void SetViewport(const Viewport& viewport) = 0;
		virtual void SetScissorRect(const ScissorRect& rect) = 0;

		virtual void Draw(
			unsigned int vertexCount, 
			unsigned int instanceCount, 
			unsigned int startVertex, 
			unsigned int startInstance) = 0;
		virtual void DrawIndexed(
			unsigned int indexCount, 
			unsigned int instanceCount, 
			unsigned int startIndex, 
			int vertexOffset, 
			unsigned int startInstance) = 0;

		virtual void Transition(Texture& texture, ResourceState state) = 0;

	protected:
		CommandBuffer() noexcept = default;
	};
}
