#include "PackageManager.h"
using namespace std;
using namespace nb;
using namespace experimental;

void nb::PackageManager::initFromFolder( std::string path )
{
	filesystem::path p( path );
	for (auto& el : filesystem::directory_iterator( p ))
	{
		if (filesystem::is_directory( el.status() ))
		{
			Package package;
			package.loadFromFolder( el.path().string() );

			m_packages.push_back( move( package ) );
			m_packagesByName[m_packages.back().getName()] = &m_packages.back();
		}
	}
}

void nb::PackageManager::save() const
{
	for (const auto& el : m_packages)
		el.save();
}

const std::list<Package>& nb::PackageManager::getLoadedPackages() const
{
	return m_packages;
}

const Package* nb::PackageManager::getPackageByName( const std::string& name ) const
{
	try
	{
		return m_packagesByName.at( name );
	}
	catch (std::exception e)
	{
		return nullptr;
	}
}

const MetaFile* nb::PackageManager::getMetaFileById( const GlobalId& globalId ) const
{
	try
	{
		return m_packagesByName.at( globalId.getPackageName() )->getMetaFileById( globalId.local );
	}
	catch (std::exception e)
	{
		return nullptr;
	}
}

/*std::pair<std::string, std::string> nb::PackageManager::splitGlobalId( std::string globalId )
{
	pair<string, string> retVal;
	auto splitPos = globalId.find( ID_SPLIT_CHAR );
	if (splitPos == string::npos)
		throw std::out_of_range( "globalId does not contain ID_SPLIT_CHAR" + ID_SPLIT_CHAR );
	retVal.first = globalId.substr( 0, splitPos );
	retVal.second = globalId.substr( splitPos + 1, string::npos );
	return retVal;
}
*/
