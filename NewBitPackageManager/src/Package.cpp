#include "Package.h"
using namespace std;
using namespace nb;
using namespace experimental;

void nb::Package::loadFromFolder( std::string path )
{
	filesystem::path p( path );
	m_name = p.filename().string();

	// list all files in the package (excluding meta files) and load meta files
	std::vector<filesystem::path> listOfFilesInPackage;

	for (auto& el : filesystem::recursive_directory_iterator( p ))
	{
		auto itpath = el.path();
		// if meta file => load
		if (itpath.extension().string() == MetaFile::EXTENSION)
		{
			string relativePath = itpath.string().substr( path.size(), string::npos );

			MetaFile metaFile;
			metaFile.loadFromFile( path, relativePath );

			if (metaFile.isLoaded())
				m_metaFilesByLocalId[metaFile.getId()] = std::move( metaFile );
			else
				throw std::exception();
		}
		// if not a meta file, but regular file => push to list of files
		else if (filesystem::is_regular_file( itpath ) && !filesystem::is_directory( itpath ))
			listOfFilesInPackage.push_back( itpath );
	}

	// remove files connected to a meta file from the list
	for (const auto& el : m_metaFilesByLocalId)
	{
		listOfFilesInPackage.erase( remove_if( listOfFilesInPackage.begin(), listOfFilesInPackage.end(), [&]( const filesystem::path& vecEl ) {
			if (el.first == vecEl.filename().stem())
				return true;
			else
				return false;
		} ), listOfFilesInPackage.end() );
	}
	// create virtual meta file for remaining files
	for (const auto& el : listOfFilesInPackage)
	{
		string relativePath = el.string().substr( path.size(), string::npos );

		MetaFile virtualMetaFile( path, relativePath );
		if (virtualMetaFile.isLoaded())
			m_metaFilesByLocalId[virtualMetaFile.getId()] = std::move( virtualMetaFile );
		else
			throw std::exception();
	}

	m_isLoaded = true;
}

bool nb::Package::isLoaded() const
{
	return m_isLoaded;
}

std::string nb::Package::getName() const
{
	return m_name;
}

std::string nb::Package::convertLocalToGlobalId( const std::string localId ) const
{
	return m_name + ":" + localId;
}

const MetaFile * nb::Package::getMetaFileById( const std::string& localId ) const
{
	try {
		return &m_metaFilesByLocalId.at( localId );
	}
	catch (std::exception e) {
		return nullptr;
	}
}
