#include "Precompiled.hpp"
#include "Scene_Stage1.hpp"

#include <stdexcept>

namespace
{
	constexpr std::string_view TriangleShader = R"hlsl(
float4 VSMain(uint vertexId : SV_VertexID) : SV_Position
{
    const float2 positions[3] =
    {
        float2(0.0f, 0.6f),
        float2(0.6f, -0.6f),
        float2(-0.6f, -0.6f)
    };
    return float4(positions[vertexId], 0.0f, 1.0f);
}

float4 PSMain() : SV_Target
{
    return float4(1.0f, 1.0f, 1.0f, 1.0f);
}
)hlsl";
}

namespace TUK::Game
{
	Scene_Stage1::Scene_Stage1(const Framework::Window& window) noexcept
		: window(window)
	{
	}

	Scene_Stage1::~Scene_Stage1() noexcept
	{
	}

	void Scene_Stage1::OnLoad()
	{
		auto* renderer = Framework::Engine::GetInstance()->GetSubsystem<Framework::RenderSubsystem>();
		if (!renderer)
		{
			throw std::runtime_error("Stage1 requires RenderSubsystem.");
		}
		auto* device = renderer->GetDevice();
		vertexShader = device->CreateVertexShader(TriangleShader);
		pixelShader = device->CreatePixelShader(TriangleShader);
	}

	void Scene_Stage1::OnUnload()
	{
		pixelShader.reset();
		vertexShader.reset();
	}

	void Scene_Stage1::OnRender(Framework::CommandBuffer& commandBuffer)
	{
		if (!vertexShader || !pixelShader)
		{
			return;
		}
		auto* renderer = Framework::Engine::GetInstance()->GetSubsystem<Framework::RenderSubsystem>();
		auto* target = renderer->GetTarget(window);
		if (!target)
		{
			return;
		}
		const int width = target->GetWidth();
		const int height = target->GetHeight();
		if (width <= 0 || height <= 0)
		{
			return;
		}

		Framework::Viewport viewport{};
		viewport.width = static_cast<unsigned int>(width);
		viewport.height = static_cast<unsigned int>(height);
		viewport.min = 0;
		viewport.max = 1;
		commandBuffer.SetTarget(*target);
		commandBuffer.SetViewport(viewport);
		commandBuffer.SetPrimitiveTopology(Framework::PrimitiveTopology::TriangleList);
		commandBuffer.SetVertexShader(*vertexShader);
		commandBuffer.SetPixelShader(*pixelShader);
		commandBuffer.Draw(3, 1, 0, 0);
	}
}
