#include "MetaFile.h"
using namespace std;
using namespace nb;
using namespace experimental;

const std::string MetaFile::EXTENSION = "._meta";
const std::string MetaFile::ATTR_PATH = "path";

std::string nb::MetaFile::generateIdFromPaths( std::string pathToPackage, std::string relativePath )
{
	string id = filesystem::path( relativePath ).replace_extension( "" ).string();
	while (true)
	{
		auto it = id.find( "\\" );
		if (it != string::npos)
		{
			id.replace( it, 1, ":" );
		}
		else
		{
			it = id.find( "/" );
			if (it == string::npos)
				break;
			else
			{
				id.replace( it, 1, ":" );
			}
		}
	}
	return id.substr( 1, string::npos );
}

nb::MetaFile::MetaFile( std::string pathToPackage,
						std::string relativePath )
{
	filesystem::path pathToPackagePath( pathToPackage );
	filesystem::path relativePathPath( relativePath );
	filesystem::path filepath = pathToPackagePath / relativePathPath;
	m_connectedFilePath = filepath.string();

	m_id = generateIdFromPaths( pathToPackage, relativePath );

	m_isLoaded = true;
}

void MetaFile::loadFromFile( std::string pathToPackage,
							 std::string relativePath )
{
	filesystem::path pathToPackagePath( pathToPackage );
	filesystem::path relativePathPath( relativePath );
	filesystem::path filepath = pathToPackagePath / relativePathPath;

	std::ifstream file;
	file.open( filepath.string() );
	if (!file.is_open())
		return;
	file >> m_data;

	m_id = generateIdFromPaths( pathToPackage, relativePath );

	auto parentPath = filepath.parent_path();
	std::string attr_path = m_data[MetaFile::ATTR_PATH];// .get<std::string>();
	if (attr_path != "")
		m_connectedFilePath = parentPath.string() + "\\" + attr_path;
	else
	{
		// find connected file
		vector<filesystem::directory_entry> possibleConnectedFiles;

		for (auto& el : filesystem::directory_iterator( parentPath ))
			if (el.path().filename().stem() == filepath.filename().stem())
				possibleConnectedFiles.push_back( el );

		// if we cannot determine a single, unique connected file => abort
		if (possibleConnectedFiles.size() != 1)
			throw exception();
		else
			m_connectedFilePath = possibleConnectedFiles.at( 0 ).path().string();
	}

	std::ifstream associatedFile;
	associatedFile.open( m_connectedFilePath );
	if (!associatedFile.is_open())
		return;

	m_isLoaded = true;
}

bool nb::MetaFile::isLoaded() const
{
	return m_isLoaded;
}

const json::json& nb::MetaFile::getData() const
{
	return m_data;
}

std::string nb::MetaFile::getConnectedFilePath() const
{
	return m_connectedFilePath;
}

const std::string& nb::MetaFile::getId() const
{
	return m_id;
}
