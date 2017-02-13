#pragma once
#include "stdafx.h"
#include "Meta.h"

namespace nb
{
	class File
	{
	public:
		File(Meta& meta);

		Meta& getMeta()const;

		std::string getPath()const;
		std::string getLocalId()const;
	};
}
