#pragma once

#include <map>
#include <memory>
#include <vector>
#include <string>
#include <concepts>
#include <stdexcept>
#include <utility>

#include "Framework/Core/GameSubsystem.hpp"
#include "Scene.hpp"

namespace TUK::Framework
{
	class Scene;

	class SceneSubsystem : public GameSubsystem
	{
	public:
		SceneSubsystem() noexcept;
		~SceneSubsystem() noexcept override;

		template <std::derived_from<Scene> TScene, class... TArgs>
		TScene* AddScene(unsigned char index, std::wstring name, TArgs&&... args)
		{
			if (scenesByIndex.contains(index) || scenesByName.contains(name))
			{
				throw std::invalid_argument("Scene index and name must be unique.");
			}
			auto scene = std::make_unique<TScene>(std::forward<TArgs>(args)...);
			auto* pointer = scene.get();
			scenesByName.emplace(std::move(name), index);
			try
			{
				scenesByIndex.emplace(index, std::move(scene));
			}
			catch (...)
			{
				std::erase_if(scenesByName, [index](const auto& entry)
				{
					return entry.second == index;
				});
				throw;
			}
			return pointer;
		}

	protected:
		void OnStartup() override;
		void OnShutdown() override;

		void EarlyUpdate() override;
		void FixedUpdate() override;
		void Update() override;
		void LateUpdate() override;

	private:
		Scene* currentScene = nullptr;
		std::map<unsigned char, std::unique_ptr<Scene>> scenesByIndex;
		std::map<std::wstring, unsigned char> scenesByName;
	};
}
