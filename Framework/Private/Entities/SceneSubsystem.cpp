#include "Precompiled.hpp"
#include "Framework/Entities/SceneSubsystem.hpp"

#include "Framework/Core/Engine.hpp"
#include "Framework/Entities/Scene.hpp"
#include "Framework/Graphics/RenderSubsystem.hpp"
#include "Framework/Graphics/CommandBuffer.hpp"

namespace TUK::Framework
{
	SceneSubsystem::SceneSubsystem() noexcept	
		: GameSubsystem(20)
	{
		
	}

	SceneSubsystem::~SceneSubsystem() noexcept
	{
		currentScene = nullptr;
	}

	void SceneSubsystem::OnStartup()
	{
		currentScene = scenesByIndex[0].get();
	}

	void SceneSubsystem::OnShutdown()
	{
		currentScene = nullptr;
	}

	void SceneSubsystem::EarlyUpdate()
	{
		
	}

	void SceneSubsystem::FixedUpdate()
	{
		if (currentScene)
		{
			currentScene->OnFixedUpdate();
		}
	}

	void SceneSubsystem::Update()
	{
		if (currentScene)
		{
			currentScene->OnUpdate();
			currentScene->OnLateUpdate();
		}
	}

	void SceneSubsystem::LateUpdate()
	{
		if (currentScene)
		{
			RenderSubsystem* renderSubsystem = Engine::GetInstance()->GetSubsystem<RenderSubsystem>();
			assert(renderSubsystem);

			CommandBuffer* commandBuffer = renderSubsystem->GetCommandBuffer();
			assert(commandBuffer);

			currentScene->OnPreRender(*commandBuffer);
			currentScene->OnRender(*commandBuffer);
			currentScene->OnPostRender(*commandBuffer);
		}
	}
}
