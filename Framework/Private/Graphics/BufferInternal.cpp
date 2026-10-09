#include "Precompiled.hpp"
#include "BufferInternal.hpp"

namespace TUK::Framework
{
	BufferInternal::BufferInternal(Microsoft::WRL::ComPtr<ID3D11Buffer> d3dBuffer) noexcept	
		: d3dBuffer(d3dBuffer)
	{
	}

	BufferInternal::~BufferInternal() noexcept
	{
		if (d3dBuffer)
		{
			d3dBuffer.Reset();
			d3dBuffer = nullptr;
		}
	}

	ID3D11Buffer* BufferInternal::GetD3D11Buffer() const noexcept
	{
		assert(d3dBuffer);
		return d3dBuffer.Get();
	}
}
