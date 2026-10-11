#pragma once 

#include <memory>
#include <string_view>

namespace TUK::Framework
{
	class Buffer;
	class CommandBuffer;
	class Texture;
	class RenderTarget;
	class SwapChain;
	class Window;
	class Shader;
	
	class GraphicsDevice
	{
	public:
		virtual ~GraphicsDevice() noexcept = default;

		GraphicsDevice(const GraphicsDevice&) noexcept = delete;
		GraphicsDevice& operator=(const GraphicsDevice&) noexcept = delete;
		
		GraphicsDevice(GraphicsDevice&&) noexcept = delete;
		GraphicsDevice& operator=(GraphicsDevice&&) noexcept = delete;

		/** 명령 제출 */
		virtual void Submit(const CommandBuffer& commandBuffer) const = 0;

		/** 스왑 체인 생성 */
		[[nodiscard]] virtual std::unique_ptr<SwapChain> CreateSwapChain(const Window& window) const = 0;

		/** 버퍼 생성 */
		[[nodiscard]] virtual std::unique_ptr<Buffer> CreateBuffer(size_t size) const = 0;

		/** 텍스쳐 생성 */
		[[nodiscard]] virtual std::unique_ptr<Texture> CreateTexture() const = 0;

		/** 렌더 타겟 생성 */
		[[nodiscard]] virtual std::unique_ptr<RenderTarget> CreateTarget() const = 0;

		[[nodiscard]] virtual std::unique_ptr<Shader> CreateVertexShader(std::string_view source,
			std::string_view entryPoint = "VSMain") const = 0;
		[[nodiscard]] virtual std::unique_ptr<Shader> CreatePixelShader(std::string_view source,
			std::string_view entryPoint = "PSMain") const = 0;

	protected:
		GraphicsDevice() noexcept = default;
	};
}
