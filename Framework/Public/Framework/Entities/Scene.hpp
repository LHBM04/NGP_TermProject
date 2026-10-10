#pragma once

namespace TUK::Framework
{
	class CommandBuffer;

	class Scene
	{
		friend class SceneSubsystem;

	public:
		virtual ~Scene() noexcept = default;

		Scene(const Scene&) = delete;
		Scene& operator=(const Scene&) = delete;

		Scene(Scene&&) = delete;
		Scene& operator=(Scene&&) = delete;

	protected:
		Scene() noexcept = default;

		virtual void OnLoad();
		virtual void OnUnload();

		virtual void OnFixedUpdate();
		virtual void OnUpdate();
		virtual void OnLateUpdate();

		virtual void OnPreRender(CommandBuffer& commandBuffer);
		virtual void OnRender(CommandBuffer& commandBuffer);
		virtual void OnPostRender(CommandBuffer& commandBuffer);
	};
}
