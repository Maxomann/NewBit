#pragma once
#include "stdafx.h"
#include "Package.h"

namespace nb
{
	class PackageManager
	{
		std::map<std::string, Package> m_packagesByName;
	public:
		void initFromFolder(std::string path);

		const std::map<std::string, Package>& getPackagesByName()const;
		const Package* getPackageByName(const std::string& name)const;
		const MetaFile* getMetaFileById(const std::string& globalId)const;

		static const char ID_SPLIT_CHAR;
		static std::pair<std::string, std::string> splitGlobalId(std::string globalId);
	};
}
