#pragma once

#include <map>
#include <memory>
#include <vector>
#include <string>

#include "Framework/Core/GameSubsystem.hpp"

namespace TUK::Framework
{
	class Scene;

	class SceneSubsystem : public GameSubsystem
	{
	public:
		SceneSubsystem() noexcept;
		~SceneSubsystem() noexcept override;

	protected:
		void OnStartup() override;
		void OnShutdown() override;

		void Update() override;
		void FixedUpdate() override;

	private:
		std::vector<std::unique_ptr<Scene>> scenes;
		std::map<unsigned char, std::unique_ptr<Scene>> scenesByIndex;
		std::map<std::wstring, std::unique_ptr<Scene>> scenesByName;
	};
}
