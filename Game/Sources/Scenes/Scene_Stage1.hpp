#pragma once

#include <memory>
#include "Framework/Entities/Scene.hpp"

namespace TUK::Framework
{
	class Shader;
	class Window;
}

namespace TUK::Game
{
	class Scene_Stage1 : public Framework::Scene
	{
	public:
		explicit Scene_Stage1(const Framework::Window& window) noexcept;
		~Scene_Stage1() noexcept override;

	protected:
		void OnLoad() override;
		void OnUnload() override;
		void OnRender(Framework::CommandBuffer& commandBuffer) override;

	private:
		const Framework::Window& window;
		std::unique_ptr<Framework::Shader> vertexShader;
		std::unique_ptr<Framework::Shader> pixelShader;
	};
}
