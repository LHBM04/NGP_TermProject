#pragma once

#include <d3d11_4.h>

#include <wrl.h>

#include "Framework/Graphics/Buffer.hpp"

namespace TUK::Framework
{
	class BufferInternal : public Buffer
	{
	public:
		explicit BufferInternal(Microsoft::WRL::ComPtr<ID3D11Buffer> d3dBuffer) noexcept;
		~BufferInternal() noexcept override;
		/** 소유권을 넘기지 않는 네이티브 객체 접근. */
		[[nodiscard]] explicit operator ID3D11Buffer*() const noexcept
		{
			return GetD3D11Buffer();
		}


		[[nodiscard]] ID3D11Buffer* GetD3D11Buffer() const noexcept;

	private:
		Microsoft::WRL::ComPtr<ID3D11Buffer> d3dBuffer;
	};
}
