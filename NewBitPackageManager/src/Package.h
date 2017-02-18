#pragma once
#include "stdafx.h"
#include "MetaFile.h"

namespace nb
{
	class Package
	{
		bool m_isLoaded = false;

		std::string m_name = "-1";

		std::map<std::string, MetaFile> m_metaFilesByLocalId;

	public:
		// Example: "/foo/bar"
		// NOT: "/foo/bar/"
		DLL_EXPORT void loadFromFolder(std::string path);
		DLL_EXPORT bool isLoaded()const;

		DLL_EXPORT std::string getName()const;

		DLL_EXPORT std::string convertLocalToGlobalId(const std::string localId)const;
		DLL_EXPORT const MetaFile* getMetaFileById(const std::string& localId)const;
	};
}
