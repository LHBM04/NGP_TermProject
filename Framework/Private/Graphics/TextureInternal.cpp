#include "Precompiled.hpp"
#include "TextureInternal.hpp"

namespace TUK::Framework
{
	TextureInternal::TextureInternal(Microsoft::WRL::ComPtr<ID3D11Texture2D> d3dTexture2D) noexcept
		: d3dTexture2D(d3dTexture2D)
	{
	}

	TextureInternal::~TextureInternal() noexcept
	{
		if (d3dTexture2D)
		{
			d3dTexture2D.Reset();
			d3dTexture2D = nullptr;
		}
	}

	ID3D11Texture2D* TextureInternal::GetD3D11Texture2D() const noexcept
	{
		assert(d3dTexture2D);
		return d3dTexture2D.Get();
	}
}
