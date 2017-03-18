#pragma once
#include "stdafx.h"

namespace nb
{
	class Connection
	{
		const std::shared_ptr<bool> m_trackablePtr;
		const std::weak_ptr<bool> m_signalTracker;
	public:
		DLL_EXPORT Connection( std::weak_ptr<bool> signalTracker );
		DLL_EXPORT Connection( const Connection& ) = delete;
		DLL_EXPORT Connection( Connection&& ) = default;

		DLL_EXPORT std::weak_ptr<bool> getTrackablePtr()const;

		DLL_EXPORT bool is_valid()const;

		DLL_EXPORT Connection& operator=( const Connection& ) = delete;
		DLL_EXPORT Connection& operator=( Connection&& ) = default;
	};

	using Connections = std::vector<Connection>;
}
