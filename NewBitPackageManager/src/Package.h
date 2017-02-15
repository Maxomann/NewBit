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
		void loadFromFolder(std::string path);
		bool isLoaded()const;

		std::string getName()const;

		std::string convertLocalToGlobalId(const std::string localId)const;
		const MetaFile* getMetaFileById(const std::string& localId)const;
	};
}
