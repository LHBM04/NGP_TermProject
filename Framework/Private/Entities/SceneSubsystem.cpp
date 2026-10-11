#include "Precompiled.hpp"
#include "Framework/Entities/SceneSubsystem.hpp"

#include "Framework/Core/Engine.hpp"
#include "Framework/Core/Game.hpp"
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
		const auto found = scenesByIndex.find(0);
		if (found == scenesByIndex.end())
		{
			Game::GetInstance()->ReportError("Initial scene with index 0 is not registered.");
			return;
		}
		currentScene = found->second.get();
		try
		{
			currentScene->OnLoad();
		}
		catch (const std::exception& error)
		{
			currentScene->OnUnload();
			currentScene = nullptr;
			Game::GetInstance()->ReportError(error.what());
		}
	}

	void SceneSubsystem::OnShutdown()
	{
		if (currentScene)
		{
			currentScene->OnUnload();
		}
		currentScene = nullptr;
		scenesByName.clear();
		scenesByIndex.clear();
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
