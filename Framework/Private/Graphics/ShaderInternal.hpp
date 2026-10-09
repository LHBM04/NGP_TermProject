#pragma once

#include <cassert>
#include <concepts>

#include <d3d11_4.h>

#include <wrl.h>

#include "Framework/Graphics/Shader.hpp"

namespace TUK::Framework
{
	class ShaderInternal : public Shader
	{
	public:
		ShaderInternal() noexcept = default;
		~ShaderInternal() noexcept override = default;

		/** 소유권을 넘기지 않는 네이티브 셰이더 접근. */
		[[nodiscard]] explicit operator ID3D11DeviceChild*() const noexcept
		{
			assert(shader);
			return shader.Get();
		}

		template <std::derived_from<ID3D11DeviceChild> TShader>
		[[nodiscard]] TShader* GetD3D11Shader() const noexcept;

	private:
		Microsoft::WRL::ComPtr<ID3D11DeviceChild> shader;
	};

	template <std::derived_from<ID3D11DeviceChild> TShader>
	TShader* ShaderInternal::GetD3D11Shader() const noexcept
	{
		assert(shader);
		return static_cast<TShader*>(shader.Get());
	}
}
