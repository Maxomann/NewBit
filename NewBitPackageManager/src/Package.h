#pragma once
#include "stdafx.h"
#include "File.h"

namespace nb
{
	class Package
	{
	public:
		void loadFromFolder(std::string path);
		bool isLoaded()const;

		std::string getName()const;

		std::string getGlobalId(std::string localId)const;
		// id can be global or local
		// returns nullptr if file does not exist
		File* getFileById(std::string Id)const;
	};
}
