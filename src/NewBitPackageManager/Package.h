#pragma once
#include "stdafx.h"
#include "MetaFile.h"

namespace nb
{
	class Package
	{
		bool m_isLoaded = false;

		std::string m_name = "-1";

		std::list<MetaFile> m_metaFiles;
		std::map<std::string, MetaFile*> m_metaFileRefsByLocalId;

	public:
		// Example: "/foo/bar"
		// NOT: "/foo/bar/"
		DLL_EXPORT void loadFromFolder( std::string path );
		DLL_EXPORT bool isLoaded()const;
		DLL_EXPORT void save()const;

		DLL_EXPORT std::string getName()const;

		DLL_EXPORT GlobalId convertLocalToGlobalId( const LocalId& localId )const;
		DLL_EXPORT const MetaFile* getMetaFileById( const LocalId& localId )const;
		DLL_EXPORT const std::list<MetaFile>& getLoadedMetaFiles()const;
	};
}
