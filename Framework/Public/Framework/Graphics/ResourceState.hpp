#pragma once

namespace TUK::Framework
{
	enum class ResourceState : unsigned char
	{
		Undefined,
		Common,
		RenderTarget,
		DepthWrite,
		DepthRead,
		ShaderResource,
		CopyDest,
		CopySource
	};
}
