#include <NewBitSignals\src\Signal.h>

using namespace std;
using namespace nb;

struct Teststruct
{
	int internalInt = -1;

	Teststruct( int var )
		: internalInt( var )
	{}

	void testmemfunc( int a )
	{
		cout << "testmemfunc: " << a << ":" << internalInt << ":*" << this << endl;
	}
};

void testfunc( int a )
{
	cout << "testfunc: " << a << endl;
}

int main()
{
	Signal<void( int )> signal0;
	Signal<void( int )> signal1;

	auto teststruct = make_unique<Teststruct>( 01 );

	signal0.connect( &testfunc );
	signal0.connect( teststruct.get(), &Teststruct::testmemfunc );

	{
		Connections cons;
		auto teststruct2 = make_unique<Teststruct>( 02 );

		signal1.connect_track( cons, &testfunc );
		signal1.connect_track( cons, teststruct2.get(), &Teststruct::testmemfunc );
	}

	Connections cons2;
	auto teststruct3 = make_unique<Teststruct>( 03 );

	{
		Signal<void( int )> signal2;
		signal2.connect_track( cons2, &testfunc );
		signal2.connect_track( cons2, teststruct3.get(), &Teststruct::testmemfunc );

		cout << "Cons2:" << endl;
		for (const auto& el : cons2)
			cout << "isValid: " << el.is_valid() << endl;
	}

	cout << "Signal0:" << endl;
	signal0.call( 80 );

	cout << "Signal1:" << endl;
	signal1.call( 90 );

	cout << "Cons2:" << endl;
	for (const auto& el : cons2)
		cout << "isValid: " << el.is_valid() << endl;

	system( "pause" );
}
