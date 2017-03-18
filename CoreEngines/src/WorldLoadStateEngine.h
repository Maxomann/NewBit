#pragma once
#include "stdafx.h"

namespace nb
{
	class WorldLoadStateEngine : public CoreEngine
	{
		std::vector<sf::Vector3i> m_loadedChunks;

	public:
		DLL_EXPORT virtual void init()override;

		DLL_EXPORT virtual bool update()override;

		DLL_EXPORT bool isChunkLoaded( const sf::Vector3i& chunkPosition )const;

		DLL_EXPORT void setChunkLoaded( const sf::Vector3i& chunkPosition, bool isLoaded );

		DLL_EXPORT const std::vector<sf::Vector3i>& getLoadedChunks()const;
	};
}
