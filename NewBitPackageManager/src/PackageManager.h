#pragma once
#include "stdafx.h"

namespace nb
{
	class PackageManager
	{
	public:
		void loadFromFolder(std::string path);
		void addPackage();

		void getLoadedPackages();
		void getPackageById();
		void getFileById();
	};
}
