#pragma once

namespace nb
{
	enum class ChunkLoadState
	{
		STATE_ERROR,
		STATE_LOADED,
		STATE_UNLOADED,
		STATE_LOADING,
		STATE_UNLOADING
	};
}
