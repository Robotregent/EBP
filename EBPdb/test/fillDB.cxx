#include <stdio.h>
#include <EBPdb/connection.hxx>
#include <EBPdb/Wohnheim.hxx>

using namespace ebp;


bool createWohnheim( QSharedPointer<connection> & c, int wohnheim )
{
	Wohnheim wh( "Wohnheim_" + QString::number(wohnheim) );
	if( !wh.create( c ) )
	{
		fprintf( stderr, "Could not create '%s'\n", wh.name().toLocal8Bit().data() );
		return false;
	}
	return true;
}

bool fillDatabase( QSharedPointer<connection> & c )
{
	for( int i=0; i<3; i++ )
	{
		if( !createWohnheim( c, i ) )
		{
			return false;
		}
	}
	return true;
}

int main( int argc, char ** argv )
{
	QSharedPointer<connection> c( new connection( "ebp_test_root", "ebp_test", "localhost", 3306 ) );
	if( !c->establish( "ebp_test_root" ) )
	{
		fprintf( stderr, "Could not connect\n" );
		return 1;
	}

	if( !fillDatabase( c ) )
		return 1;
	else
		return 0;
}
