#pragma once
#include "stdafx.h"
#include "Package.h"

namespace nb
{
	class PackageManager
	{
		std::map<std::string, Package> m_packagesByName;
	public:
		DLL_EXPORT void initFromFolder( std::string path );
		DLL_EXPORT void save()const;

		DLL_EXPORT const std::map<std::string, Package>& getPackagesByName()const;
		DLL_EXPORT const Package* getPackageByName( const std::string& name )const;
		DLL_EXPORT const MetaFile* getMetaFileById( const std::string& globalId )const;

		DLL_EXPORT static const char ID_SPLIT_CHAR;
		DLL_EXPORT static std::pair<std::string, std::string> splitGlobalId( std::string globalId );
	};
}
