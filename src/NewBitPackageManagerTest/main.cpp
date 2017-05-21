#include "stdafx.h"
using namespace std;
using namespace nb;

int main()
{
	PackageManager packageManager;
	packageManager.initFromFolder( "./data/debug_packageManager" );

	//const std::list<Package>& pkgsByName = packageManager.getLoadedPackages();

	const Package* newPackage = packageManager.getPackageByName( "NewPackage" );
	const Package* testpackage = packageManager.getPackageByName( "Testpackage" );

	const MetaFile* npm1 = packageManager.getMetaFileById( "NewPackage:mario1" );
	const MetaFile* npm2 = packageManager.getMetaFileById( "NewPackage:mario2" );
	const MetaFile* nptf = packageManager.getMetaFileById( "NewPackage:textfile" );
	const MetaFile* npmt = packageManager.getMetaFileById( "NewPackage:textures:myTexture" );

	const MetaFile* tpm1 = packageManager.getMetaFileById( "Testpackage:mario1" );
	const MetaFile* tpm2 = packageManager.getMetaFileById( "Testpackage:mario2" );
	const MetaFile* tpm3 = packageManager.getMetaFileById( "Testpackage:mario3" );
	const MetaFile* tptf = packageManager.getMetaFileById( "Testpackage:textfile" );

	//

	cout << "-- Package names:" << endl;
	cout << newPackage->getName() << endl;
	cout << testpackage->getName() << endl;

	//

	const MetaFile* _npm1 = newPackage->getMetaFileById( "mario1" );
	const MetaFile* _npm2 = newPackage->getMetaFileById( "mario2" );
	const MetaFile* _nptf = newPackage->getMetaFileById( "textfile" );
	const MetaFile* _npmt = newPackage->getMetaFileById( "textures:myTexture" );

	const MetaFile* _tpm1 = testpackage->getMetaFileById( "mario1" );
	const MetaFile* _tpm2 = testpackage->getMetaFileById( "mario2" );
	const MetaFile* _tpm3 = testpackage->getMetaFileById( "mario3" );
	const MetaFile* _tptf = testpackage->getMetaFileById( "textfile" );

	cout << boolalpha;
	cout << "-- Compare MetaFiles:" << endl;
	cout << ( npm1 == _npm1 ) << endl;
	cout << ( npm2 == _npm2 ) << endl;
	cout << ( nptf == _nptf ) << endl;
	cout << ( npmt == _npmt ) << endl;

	cout << ( tpm1 == _tpm1 ) << endl;
	cout << ( tpm2 == _tpm2 ) << endl;
	cout << ( tpm3 == _tpm3 ) << endl;
	cout << ( tptf == _tptf ) << endl;

	//

	cout << "-- Local ID, Global ID, Connected Filepath:" << endl;
	cout << npm1->getId() << endl;
	cout << newPackage->convertLocalToGlobalId( npm1->getId() ) << endl;
	cout << npm1->getConnectedFilePath() << endl;
	cout << npm2->getId() << endl;
	cout << newPackage->convertLocalToGlobalId( npm2->getId() ) << endl;
	cout << npm2->getConnectedFilePath() << endl;
	cout << nptf->getId() << endl;
	cout << newPackage->convertLocalToGlobalId( nptf->getId() ) << endl;
	cout << nptf->getConnectedFilePath() << endl;
	cout << npmt->getId() << endl;
	cout << newPackage->convertLocalToGlobalId( npmt->getId() ) << endl;
	cout << npmt->getConnectedFilePath() << endl;

	cout << tpm1->getId() << endl;
	cout << testpackage->convertLocalToGlobalId( tpm1->getId() ) << endl;
	cout << tpm1->getConnectedFilePath() << endl;
	cout << tpm2->getId() << endl;
	cout << testpackage->convertLocalToGlobalId( tpm2->getId() ) << endl;
	cout << tpm2->getConnectedFilePath() << endl;
	cout << tpm3->getId() << endl;
	cout << testpackage->convertLocalToGlobalId( tpm3->getId() ) << endl;
	cout << tpm3->getConnectedFilePath() << endl;
	cout << tptf->getId() << endl;
	cout << testpackage->convertLocalToGlobalId( tptf->getId() ) << endl;
	cout << tptf->getConnectedFilePath() << endl;

	cout << "-----------------" << endl;
	cout << "NewBitPackageManagerTest complete" << endl;
	system( "pause" );

	packageManager.save();
}
