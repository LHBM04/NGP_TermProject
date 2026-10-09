#pragma once

#include <d3d11_4.h>

#include <wrl.h>

#include "Framework/Graphics/Texture.hpp"

namespace TUK::Framework
{
	class TextureInternal : public Texture
	{
	public:
		explicit TextureInternal(Microsoft::WRL::ComPtr<ID3D11Texture2D> d3dTexture2D) noexcept;
		~TextureInternal() noexcept override;
		/** 소유권을 넘기지 않는 네이티브 객체 접근. */
		[[nodiscard]] explicit operator ID3D11Texture2D*() const noexcept
		{
			return GetD3D11Texture2D();
		}


		/** D3D11 텍스쳐 Getter */
		[[nodiscard]] ID3D11Texture2D* GetD3D11Texture2D() const noexcept;

	private:
		Microsoft::WRL::ComPtr<ID3D11Texture2D> d3dTexture2D;
	};
}
