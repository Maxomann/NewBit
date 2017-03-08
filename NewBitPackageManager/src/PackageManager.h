#pragma once
#include "stdafx.h"
#include "Package.h"

namespace nb
{
	class PackageManager
	{
		std::list<Package> m_packages;
		std::map<std::string, Package*> m_packagesByName;
	public:
		DLL_EXPORT void initFromFolder( std::string path );
		DLL_EXPORT void save()const;

		DLL_EXPORT const std::list<Package>& getLoadedPackages()const;
		DLL_EXPORT const Package* getPackageByName( const std::string& name )const;
		DLL_EXPORT const MetaFile* getMetaFileById( const GlobalId& globalId )const;
	};
}
