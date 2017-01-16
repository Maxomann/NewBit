#pragma once
#include "stdafx.h"

namespace nb
{
	class Trackable
	{
		std::shared_ptr<bool> m_ref;

	public:
		std::weak_ptr<bool> getTrackablePtr()const
		{
			return m_ref;
		};
	};
}
